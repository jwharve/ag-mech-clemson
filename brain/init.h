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
Goes from x-min to x-max, y-min to y-max, then z-min to z-max.
*/
int calibrate();

#endif
