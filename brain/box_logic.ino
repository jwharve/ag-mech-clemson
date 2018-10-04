class Box
{
  public:
    Box(int Xin, int Yin, int numXin, int numYin, int X0in, int Y0in);
    int X, Y; // width (X) and length (Y) of the box [steps]
    int numX, numY; // number of units in each direction [count]
    int X0, Y0; // origin of the box in the overall system (X[zero] and Y[zero]) [steps]
    
    int goToUnit(int xInd, int yInd);
    
    float unitX, unitY; // width (x) and length (y) of each unit [steps]
};

Box::Box(int Xin, int Yin, int numXin, int numYin, int X0in, int Y0in)
{
  this->X = Xin;
  this->Y = Yin;
  this->numX = numXin;
  this->numY = numYin;
  this->X0 = X0in;
  this->Y0 = Y0in;

  this->unitX = (float)Xin / (float)numXin;
  this->unitY = (float)Yin / (float)numYin;
}

Box::goToUnit(int xInd, int yInd)
{
  go(this->X0 + xInd * this->unitX, this->Y0 + yInd * this->unitY,z_range);
}

