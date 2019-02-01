#ifndef MOVE_H
#define MOVE_H

#include <Arduino.h>
#include "globals.h"
#include "definitions.h"
#include "pins.h"

/*
This function goes to the coordinates (x,y,z)
The pattern of motion is: move head up go to (x,y) then move down to z
*/
int go(int x, int y, int z);

/*
This function moves 1 step in dir (<0 is down, >0 is up) in the x direction
*/
void stepX(int dir);

/*
This function moves 1 step in dir (<0 is down, >0 is up) in the x direction
*/
void stepY(int dir);

/*
This function moves 1 step in dir (<0 is down, >0 is up) in the x direction
*/
void stepZ(int dir);

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

#endif
