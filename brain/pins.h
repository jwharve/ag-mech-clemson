#ifndef PINS_H
#define PINS_H

/* SWAPPED X AND Z */
/* SWAPPED Z_MIN AND Z_MAX */

#define Z_MIN_PIN          14
#define Z_MAX_PIN          19

#define Y_MIN_PIN          18
#define Y_MAX_PIN          15

#define X_MIN_PIN          3
#define X_MAX_PIN          2


#define X_STEP_PIN         54
#define X_DIR_PIN          55
#define X_ENABLE_PIN       38

#define Y_STEP_PIN         60
#define Y_DIR_PIN          61
#define Y_ENABLE_PIN       56

#define Z_STEP_PIN         46
#define Z_DIR_PIN          48
#define Z_ENABLE_PIN       62

#define E_STEP_PIN         26
#define E_DIR_PIN          28
#define E_ENABLE_PIN       24

#define SDPOWER            -1
#define SDSS               53
#define LED_PIN            13

#define FAN_PIN            9

#define PS_ON_PIN          12
#define KILL_PIN           -1

#define VACUUM_PIN       10
#define HEATER_1_PIN       8
#define TEMP_0_PIN          13   // ANALOG NUMBERING
#define TEMP_1_PIN          14   // ANALOG NUMBERING

#define PUMP_PIN 57

#define START_PIN 57 // unused

// pins for button controller
#define X_P 42
#define X_N 64
#define Y_P 44
#define Y_N 40
#define Z_P 63
#define Z_N 59
#define P_1 66
#define P_2 65


#endif
