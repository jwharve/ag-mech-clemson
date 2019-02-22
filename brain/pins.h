#ifndef PINS_H
#define PINS_H

/* SWAPPED X AND Z */
/* SWAPPED Z_MIN AND Z_MAX */

#define Z_STEP_PIN         54
#define Z_DIR_PIN          55
#define Z_ENABLE_PIN       56
#define Z_MIN_PIN          14
#define Z_MAX_PIN          19

#define Y_STEP_PIN         46
#define Y_DIR_PIN          48
#define Y_ENABLE_PIN       38
#define Y_MIN_PIN          18
#define Y_MAX_PIN  		   15

#define X_STEP_PIN         26
#define X_DIR_PIN          28
#define X_ENABLE_PIN       62
#define X_MAX_PIN          2
#define X_MIN_PIN          3

#define E_STEP_PIN         60
#define E_DIR_PIN          61
#define E_ENABLE_PIN       24

#define Q_STEP_PIN         36
#define Q_DIR_PIN          34
#define Q_ENABLE_PIN       30

#define SDPOWER            -1
#define SDSS               53
#define LED_PIN            13

#define FAN_PIN            9

#define PS_ON_PIN          12
#define KILL_PIN           -1

#define HEATER_0_PIN       10
#define HEATER_1_PIN       8
#define TEMP_0_PIN          13   // ANALOG NUMBERING
#define TEMP_1_PIN          14   // ANALOG NUMBERING

#define START_PIN 57 // unused

// pins for button controller
// Z then X then Y then pumps (starting at ground)
#define X_P 40
#define X_N 64
#define Y_P 42
#define Y_N 44
#define Z_P 63
#define Z_N 59
#define P_1 66
#define P_2 65


#endif
