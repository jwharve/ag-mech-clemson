#ifndef BOX_LOGIC_H
#define BOX_LOGIC_H

class Box
{
  public:
    Box(int Xin, int Yin, int numXin, int numYin, int X0in, int Y0in);
    int X, Y; // width (X) and length (Y) of the box [steps]
    int numX, numY; // number of units in each direction [count]
    int X0, Y0; // (X[zero] and Y[zero]) middle of unit (0,0) in the overall system  [steps]
    
    int goToUnit(int xInd, int yInd);
    
    float unitX, unitY; // width (x) and length (y) of each unit [steps]
};

#endif
