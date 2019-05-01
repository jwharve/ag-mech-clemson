#ifndef INIT_H
#define INIT_H

#include <Arduino.h>
#include "definitions.h"
#include "pins.h"
#include "globals.h"

#include "move.h"

#define ACCEL_INIT 1.003
#define NUM_RAMP_INIT 186
#define START_DELAY_INIT 1750.0
#define MIN_DELAY_INIT 1000.0

/*
Does pinMode(...) for all pins
*/
void setupPins(void);

/*
This function moves the machine to the min x, min y, and max z
then sets the limits and positions to what they should be
(assumes nothing moves)
*/
void zero()

/*
This function calibrates the endpoints of the machine
It provides a safety margin of SAFETY steps
Moves up, then min_x to max_x to min_y to max_y, then min_z to max_z
*/
void calibrate();

#endif
