/* Automatically generated nanopb header */
/* Generated by nanopb-0.2.5 at Sat Apr 18 09:18:37 2015. */

#ifndef _PB_OPENIOT_PB_H_
#define _PB_OPENIOT_PB_H_
#include <pb.h>

#ifdef __cplusplus
extern "C" {
#endif

/* Enum definitions */
typedef enum _OpenIoT_Command {
    OpenIoT_Command_REGISTER = 1,
    OpenIoT_Command_ACKNOWLEDGE = 2,
    OpenIoT_Command_DEVICELOCATION = 3,
    OpenIoT_Command_DEVICEALERT = 4,
    OpenIoT_Command_DEVICEMEASUREMENT = 5
} OpenIoT_Command;

typedef enum _Device_Command {
    Device_Command_REGISTER_ACK = 1
} Device_Command;

typedef enum _Device_RegistrationAckState {
    Device_RegistrationAckState_NEW_REGISTRATION = 1,
    Device_RegistrationAckState_ALREADY_REGISTERED = 2,
    Device_RegistrationAckState_REGISTRATION_ERROR = 3
} Device_RegistrationAckState;

typedef enum _Device_RegistrationAckError {
    Device_RegistrationAckError_INVALID_SPECIFICATION = 1,
    Device_RegistrationAckError_SITE_TOKEN_REQUIRED = 2,
    Device_RegistrationAckError_NEW_DEVICES_NOT_ALLOWED = 3
} Device_RegistrationAckError;

/* Struct definitions */
typedef struct _Device {
    uint8_t dummy_field;
} Device;

typedef struct _OpenIoT {
    uint8_t dummy_field;
} OpenIoT;

typedef struct _Device_Header {
    Device_Command command;
    bool has_originator;
    char originator[30];
    bool has_nestedPath;
    char nestedPath[50];
    bool has_nestedSpec;
    char nestedSpec[40];
} Device_Header;

typedef struct _Device_RegistrationAck {
    Device_RegistrationAckState state;
    bool has_errorType;
    Device_RegistrationAckError errorType;
    bool has_errorMessage;
    char errorMessage[70];
} Device_RegistrationAck;

typedef struct _OpenIoT_Acknowledge {
    char hardwareId[40];
    bool has_message;
    char message[70];
} OpenIoT_Acknowledge;

typedef struct _OpenIoT_Header {
    OpenIoT_Command command;
    bool has_originator;
    char originator[30];
} OpenIoT_Header;

typedef struct _OpenIoT_Measurement {
    char measurementId[30];
    char measurementValue[16];
} OpenIoT_Measurement;

typedef struct _OpenIoT_Metadata {
    pb_callback_t name;
    pb_callback_t value;
} OpenIoT_Metadata;

typedef struct _OpenIoT_DeviceAlert {
    char hardwareId[40];
    char alertType[40];
    char alertMessage[70];
    bool has_eventDate;
    uint64_t eventDate;
    pb_callback_t metadata;
} OpenIoT_DeviceAlert;

typedef struct _OpenIoT_DeviceLocation {
    char hardwareId[40];
    char latitude[10];
    char longitude[10];
    bool has_elevation;
    char elevation[10];
    bool has_eventDate;
    uint64_t eventDate;
    pb_callback_t metadata;
} OpenIoT_DeviceLocation;

typedef struct _OpenIoT_DeviceMeasurements {
    char hardwareId[40];
    size_t measurement_count;
    OpenIoT_Measurement measurement[5];
    bool has_eventDate;
    uint64_t eventDate;
    pb_callback_t metadata;
} OpenIoT_DeviceMeasurements;

typedef struct _OpenIoT_RegisterDevice {
    char hardwareId[40];
    char specificationToken[40];
    pb_callback_t metadata;
    pb_callback_t siteToken;
} OpenIoT_RegisterDevice;

/* Default values for struct fields */

/* Field tags (for use in manual encoding/decoding) */
#define Device_Header_command_tag                1
#define Device_Header_originator_tag             2
#define Device_Header_nestedPath_tag             3
#define Device_Header_nestedSpec_tag             4
#define Device_RegistrationAck_state_tag         1
#define Device_RegistrationAck_errorType_tag     2
#define Device_RegistrationAck_errorMessage_tag  3
#define OpenIoT_Acknowledge_hardwareId_tag     1
#define OpenIoT_Acknowledge_message_tag        2
#define OpenIoT_Header_command_tag             1
#define OpenIoT_Header_originator_tag          2
#define OpenIoT_Measurement_measurementId_tag  1
#define OpenIoT_Measurement_measurementValue_tag 2
#define OpenIoT_Metadata_name_tag              1
#define OpenIoT_Metadata_value_tag             2
#define OpenIoT_DeviceAlert_hardwareId_tag     1
#define OpenIoT_DeviceAlert_alertType_tag      2
#define OpenIoT_DeviceAlert_alertMessage_tag   3
#define OpenIoT_DeviceAlert_eventDate_tag      4
#define OpenIoT_DeviceAlert_metadata_tag       5
#define OpenIoT_DeviceLocation_hardwareId_tag  1
#define OpenIoT_DeviceLocation_latitude_tag    2
#define OpenIoT_DeviceLocation_longitude_tag   3
#define OpenIoT_DeviceLocation_elevation_tag   4
#define OpenIoT_DeviceLocation_eventDate_tag   5
#define OpenIoT_DeviceLocation_metadata_tag    6
#define OpenIoT_DeviceMeasurements_hardwareId_tag 1
#define OpenIoT_DeviceMeasurements_measurement_tag 2
#define OpenIoT_DeviceMeasurements_eventDate_tag 3
#define OpenIoT_DeviceMeasurements_metadata_tag 4
#define OpenIoT_RegisterDevice_hardwareId_tag  1
#define OpenIoT_RegisterDevice_specificationToken_tag 2
#define OpenIoT_RegisterDevice_metadata_tag    3
#define OpenIoT_RegisterDevice_siteToken_tag   4

/* Struct field encoding specification for nanopb */
extern const pb_field_t OpenIoT_fields[1];
extern const pb_field_t OpenIoT_Header_fields[3];
extern const pb_field_t OpenIoT_Metadata_fields[3];
extern const pb_field_t OpenIoT_RegisterDevice_fields[5];
extern const pb_field_t OpenIoT_Acknowledge_fields[3];
extern const pb_field_t OpenIoT_DeviceLocation_fields[7];
extern const pb_field_t OpenIoT_DeviceAlert_fields[6];
extern const pb_field_t OpenIoT_Measurement_fields[3];
extern const pb_field_t OpenIoT_DeviceMeasurements_fields[5];
extern const pb_field_t Device_fields[1];
extern const pb_field_t Device_Header_fields[5];
extern const pb_field_t Device_RegistrationAck_fields[4];

/* Maximum encoded size of messages (where known) */
#define OpenIoT_size                           0
#define OpenIoT_Header_size                    38
#define OpenIoT_Acknowledge_size               114
#define OpenIoT_Measurement_size               50
#define Device_size                              0
#define Device_Header_size                       132
#define Device_RegistrationAck_size              84

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif
