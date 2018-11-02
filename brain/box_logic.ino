Tool head;

void Tool::pickup(int tool_num)
{
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
