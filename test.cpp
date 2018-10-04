#include <stdio.h>

int z_range = 100;

void go(int x, int y, int z)
{
  printf("%d %d %d\n", x, y, z);
  return;
}

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

Box::Box(int Xin, int Yin, int numXin, int numYin, int X0in, int Y0in)
{
  X = Xin;
  Y = Yin;
  numX = numXin;
  numY = numYin;
  X0 = X0in;
  Y0 = Y0in;

  unitX = (float)Xin / (float)numXin;
  unitY = (float)Yin / (float)numYin;
}

int Box::goToUnit(int xInd, int yInd)
{
  go(X0 + xInd * unitX, Y0 + yInd * unitY,z_range);
  return 1;
}

int main(void)
{
	Box one(10,10,5,5,0,0);
	one.goToUnit(2,3);
}
