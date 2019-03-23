#ifndef MOVE_H
#define MOVE_H

#include <Arduino.h>
#include "globals.h"
#include "definitions.h"
#include "pins.h"

/*
moves a certain number of steps in a direction along an axis
*/
int move(char axis, int dir, int num_steps);

/*
This function goes to the coordinates (x,y,z)
The pattern of motion is: move head up go to (x,y) then move down to z
*/
int go(int x, int y, int z);

/*
Interrupt code for hitting endstops
*/
void endstopInterrupt(void);


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
