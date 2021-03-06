#include "pb.h"
#include "pb_decode.h"
#include "pb_encode.h"
#include "sitewhere.h"
#include "sitewhere-arduino.pb.h"

#include "proton/message.h"
#include "proton/messenger.h"
#include "pncompat/misc_funcs.inc"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <time.h>
#include <assert.h>

#define check(messenger)                                                     \
  {                                                                          \
    if(pn_messenger_errno(messenger))                                        \
    {                                                                        \
      die(__FILE__, __LINE__, pn_error_text(pn_messenger_error(messenger))); \
    }                                                                        \
  }                                                                          \

void die(const char *file, int line, const char *message)
{
  fprintf(stderr, "%s:%i: %s\n", file, line, message);
  exit(1);
}

void usage(void)
{
  printf("Usage: agent [-o addr] [message] -i [hardwareId] -s [specToken] -m|a|i [mode]\n");
  printf("-o     \tThe target address [amqp[s]://domain[/name]]\n");
  printf("-i     \thardwhereId to uniquely identify this device\n");
  printf("-s     \tspecificationToken assigned by device onboarding server\n");
  printf("-m     \tmeasurement mode, with key:value argument,eg: cpu.utilization:0.55\n");
  printf("-a     \talert mode, with [key:value] format argument,eg: egnine.overheat:temperature is above 1000\n");
  printf("-l     \tlocation mode, with [lat:lon:ele] format argument,eg: 23.0000:12.0000:154.0000\n");
  exit(0);
}


/** Unique hardware id for this device */
char* hardwareId = "";
/** Device specification token for hardware configuration */
char* specificationToken = "";
/** Outbound AMQP url*/
char* outboundAddress = "";

static char * payloadkey = (char *) "payload";

int MODE_NULL = 0;
int MODE_REGISTER = 1;
int MODE_MEASUREMENT = 2;
int MODE_ALERT = 3;
int MODE_LOCATION = 4;


/** Message buffer */
uint8_t buffer[300];

/** Keeps up with whether we have registered */
bool registered = true;

/** Timestamp for last event */
struct timeval lastEvent;
struct timeval now;

/** Send message to AMQP broker */
void send_message(char * address, char * payload) {

  pn_messenger_t * messenger = pn_messenger(NULL);
  pn_messenger_start(messenger);  

  pn_message_t * message = pn_message();
  pn_message_set_address(message, address);
  pn_data_t * data = pn_message_properties(message);
  pn_data_put_map(data);
  pn_data_enter(data);
  pn_data_put_string(data, pn_bytes(strlen(payloadkey), payloadkey));
  pn_data_put_string(data, pn_bytes(strlen(payload), payload));
  pn_data_exit(data);
  
  pn_messenger_put(messenger, message);
  check(messenger);
  pn_messenger_send(messenger, -1);
  check(messenger);

  pn_messenger_stop(messenger);
  pn_messenger_free(messenger);
  pn_message_free(message);
  
}

char** str_split(char* a_str, const char a_delim)
{
    char** result    = 0;
    size_t count     = 0;
    char* tmp        = a_str;
    char* last_comma = 0;
    char delim[2];
    delim[0] = a_delim;
    delim[1] = 0;

    /* Count how many elements will be extracted. */
    while (*tmp)
    {
        if (a_delim == *tmp)
        {
            count++;
            last_comma = tmp;
        }
        tmp++;
    }

    /* Add space for trailing token. */
    count += last_comma < (a_str + strlen(a_str) - 1);

    /* Add space for terminating null string so caller
       knows where the list of returned strings ends. */
    count++;

    result = malloc(sizeof(char*) * count);

    if (result)
    {
        size_t idx  = 0;
        char* token = strtok(a_str, delim);

        while (token)
        {
            assert(idx < count);
            *(result + idx++) = strdup(token);
            token = strtok(0, delim);
        }
        assert(idx == count - 1);
        *(result + idx) = 0;
    }

    return result;
}


int main(int argc, char** argv) {
  opterr = 0;
  int c = 0;
  int mode = MODE_NULL;
  char* measurementString;
  char* alertString;
  char* locationString;
  
  while((c = getopt(argc, argv, "hro:i:s:m::a::l::")) != -1) {
    
    switch(c) {
      case 'h': usage(); break;
      case 'o': outboundAddress = optarg; break;
      case 'i': hardwareId = optarg; break;
      case 's': specificationToken = optarg; break;
      case 'r': 
        mode = MODE_REGISTER;
        break;  
      case 'm': 
        mode = MODE_MEASUREMENT; 
        measurementString = optarg;
        break;  
      case 'a': 
        mode = MODE_ALERT;
        alertString = optarg;
        break;  
      case 'l': 
        mode = MODE_LOCATION; 
        locationString = optarg;
        break;  
      case '?':
        fprintf(stderr, "Wrong option -%c \n", optopt);
        return 1;
  
      default:
        abort();
    }
  }
  
  unsigned int len = 0;
  switch(mode)
  {
    case MODE_REGISTER:
      
      if (len = sw_register(hardwareId, specificationToken, buffer, sizeof(buffer), NULL)) {
        send_message(outboundAddress, buffer);
        printf("sent register message.");
      } else {
        printf("create register message failed.");
      }
      
      break;
      
    case MODE_MEASUREMENT:
      
      char** tokens = str_split(measurementString,":");
      if (len = sw_measurement(hardwareId, *tokens, *(tokens+1), 0, buffer, sizeof(buffer), NULL)) {
        send_message(outboundAddress, buffer);
        printf("sent measurement message.");
      } else {
        printf("create measurement message failed.");
      }
      
      break;
      
    case MODE_ALERT:
      
      char** tokens = str_split(alertString,":");
      if (len = sw_alert(hardwareId, *tokens, *(tokens+1), 0, buffer, sizeof(buffer), NULL)) {
        send_message(outboundAddress, buffer);
        printf("sent alert message.");
      } else {
        printf("create alive message failed.");
      }
      
      break;
      
    case MODE_LOCATION:
      char** tokens = str_split(locationString,":");
      if (len = sw_alert(hardwareId, *tokens, *(tokens+1),*(tokens+2), 0, buffer, sizeof(buffer), NULL)) {
        send_message(outboundAddress, buffer);
        printf("sent location message.");
      } else {
        printf("create location message failed.");
      }
      
      break;
      
    default:
      abort();  
          
  }

}