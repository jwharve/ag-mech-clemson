#ifndef BOX_LOGIC_H
#define BOX_LOGIC_H

#include "move.h"
#include <stdio.h>

#define SLIDE_STEPS 30

#define EMPTY 0

class Tool
{
  public:
    int offsetX = 0; // x offset of tool from middle of tool head
    int offsetY = 0; // y offset of tool from middle of tool head
    int currentTool = EMPTY; // current tool
    int depth = 0; // depth of tool from bottom of tool head
    
    // location of tool storage in X, Y, Z
    int toolLocX = 0; // UPDATE THESE VALUES
    int toolLocY = 0;
    int toolLocZ = 0;
    
    void pickup(int tool_num); // picks up a certain tool
};

struct plantInfo
{
  int height = 0;
};

class Box
{
  public:
    Box(int Xin, int Yin, int numXin, int numYin, int X0in, int Y0in);
    int X, Y; // width (X) and length (Y) of the box [steps]
    int numX, numY; // number of units in each direction [count]
    int X0, Y0; // (X[zero] and Y[zero]) middle of unit (0,0) in the overall system  [steps]

    struct plantInfo ** plants;
    
    int goToUnit(int xInd, int yInd);
    
    float unitX, unitY; // width (x) and length (y) of each unit [steps]

    ~Box();
};

extern volatile int z_range;

extern Tool head;

#endif
