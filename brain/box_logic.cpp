#include "box_logic.h"

Box::Box(int Xin, int Yin, int numXin, int numYin, int X0in, int Y0in)
{
  X = Xin;
  Y = Yin;
  numX = numXin;
  numY = numYin;
  X0 = X0in;
  Y0 = Y0in;

  unitX = (float)Xin/ (float)(numXin-1);
  unitY = (float)Yin/ (float)(numYin-1);
}

int Box::goToUnit(int xInd, int yInd)
{
  Serial.println(X0 + xInd * unitX);
  Serial.println(Y0 + yInd * unitY);
  go(X0 + xInd * unitX, Y0 + yInd * unitY, 0);
  return 1;
}
