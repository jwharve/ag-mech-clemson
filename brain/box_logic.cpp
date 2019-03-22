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

int Box::seed(int xInd, int yInd, int xMin, int xMax)
{
	int i,j;
	
	for (i = 0; i < numX; i++)
	{
		for (j = 0; j < numY; j++)
		{
			if (i >= xMin && i <= xMax && !(i == xInd && j == yInd))
			{
				goToUnit(xInd,yInd);
				vacuum(ON);
				delay(500);
				goToUnit(i,j);
				vacuum(OFF);
			}
		}
	}

	return 0;
}
