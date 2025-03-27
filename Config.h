#ifndef CONFIG_H
#define CONFIG_H

#define ENABLE_MACHINE_LEARNING true // Dishwasher learn actions time using
#define ALLOW_SHUTDOWN_AFTER_START_S 4
#define BOOL_SENSORS_MIN_DETECT_VALUE 500
#define ENABLE_SENSORS_DEBUG false // some problems with lcd 
#define TEMP_DEBUG_VALUE false
#define SENSORS_DEBUG_INTERVAL_MS 5000
#define SENSORS_READ_INTERVAL_MS 100
#define MAX_REALISTIC_TEMPERATURE 100
#define MIN_REALISTIC_TEMPERATURE 0
#define ENABLE_ACTIONS_DEBUG true
#define ACTION_SOAPDOOR_WAIT 60 // seconds
#define MAX_ALLOWED_TIME_ADD_WATER 36 // seconds   38259 ms
#define MAX_ALLOWED_TIME_HEAT_WATER 60*20 // seconds
#define WATER_EMPTY_PUMP_TIME 19 // seconds
#define TEMP_OFFSET 2 // stop heating before 2'C from target temp

#endif