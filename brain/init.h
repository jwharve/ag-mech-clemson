#ifndef INIT_H
#define INIT_H

#include <Arduino.h>
#include "definitions.h"
#include "pins.h"
#include "globals.h"

#include "move.h"


void setupPins(void);

/*
This function calibrates the endpoints of the machine
It provides a safety margin of SAFETY steps
Moves up, then min_x to max_x to min_y to max_y, then min_z to max_z
*/
int calibrate();

#endif
