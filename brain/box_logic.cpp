<<<<<<< HEAD:brain/box_logic.cpp
#include "box_logic.h"
=======
Tool head;

void Tool::pickup(int tool_num)
{
  // maybe read in from file
  switch (tool_num)
  {
    default:
      offsetX = 0;
      offsetY = 0;
      currentTool = EMPTY;
      depth = 0;

      toolLocX = 0;
      toolLocY = 0;
      toolLocZ = 0;
      break;
  }

  // go to top of tool
  go(toolLocX, toolLocY, toolLocZ);

  // slide tool out
  int i;
  for (i = 0; i < SLIDE_STEPS; i++)
  {
    stepX(-1);
  }
}
>>>>>>> 1740f1b1703c3a3fc5e9d57fb9c9fde480137377:brain/box_logic.ino

Box::Box(int Xin, int Yin, int numXin, int numYin, int X0in, int Y0in)
{
  X = Xin;
  Y = Yin;
  numX = numXin;
  numY = numYin;
  X0 = X0in;
  Y0 = Y0in;

  unitX = (float)Xin/ (float)(numX-1);
  unitY = (float)Yin/ (float)(numY-1);

  plants = (struct plantInfo **)malloc(numX*sizeof(struct plantInfo *));
  int i,j;
  for (i = 0; i < numXin; i++)
  {
    plants[i] = (struct plantInfo *)malloc(numY*sizeof(struct plantInfo));
    for (j = 0; j < numY; j++)
    {
      plants[i][j].height = 0;
    }
  }
}

int Box::goToUnit(int xInd, int yInd)
{
  Serial.println(X0 + xInd * unitX);
  Serial.println(Y0 + yInd * unitY);
  go(X0 + xInd * unitX, Y0 + yInd * unitY, 0);
  return 1;
}

<<<<<<< HEAD:brain/box_logic.cpp
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
=======
Box::~Box(void)
{
  int i;
  for (i = 0; i < numX; i++)
  {
    free(plants[i]);
  }
  free(plants);
>>>>>>> 1740f1b1703c3a3fc5e9d57fb9c9fde480137377:brain/box_logic.ino
}
