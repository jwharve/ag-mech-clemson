extern volatile int z_range;

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
  go(X0 + xInd * unitX, Y0 + yInd * unitY, z_range);
  return 1;
}
