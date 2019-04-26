#ifndef MOVE_H
#define MOVE_H

#include <Arduino.h>
#include "globals.h"
#include "definitions.h"
#include "pins.h"

#define START_DELAY 1750.0 /* cannot be larger than 16000, in units of microseconds */
#define ACCEL 1.003
#define NUM_RAMP 330 /* number of accelerations need to get to full speed (1) to calculate: log(START_DELAY/MIN_DELAY)/log(ACCEL)*/
#define MIN_DELAY 650.0 /* minimum delay -> top speed (uS) */

/*
moves a certain number of steps in a direction along an axis
ramps according to the START_DELAY, ACCEL, and NUM_RAMP "#define"'s
*/
int move(char axis, int dir, int num_steps);

/*
This function goes to the coordinates (x,y,z)
The pattern of motion is: move head up (1/4 of z_range) go to (x,y) then move down to z
*/
int go(int x, int y, int z);

/*
Interrupt code for hitting endstops
not implemented
*/
void endstopInterrupt(void);

/*
Reads the buttons and moves appropriately
*/
void buttonMove();


/*
This function sets the direction for the motor for the three axes
'x', 'y', and 'z'
*/
void setDir(char axis, int dir);

/*
This function sets the vaccum on or off
*/
void vacuum(char state);

/*
This function turns the pump on or off
*/
void pump(char state);

#endif
