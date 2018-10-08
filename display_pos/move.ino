/*
This function goes to the coordinates (x,y,z)
The pattern of motion is: move head up go to (x,y) then move down to z
*/
int go(int x, int y, int z)
{
  if (x < 0 || y < 0 || z < 0 || x > x_range || y > y_range || z > z_range)
  {
    Serial.print("ERR");
    return -1;
  }
  // MOVE HEAD UP
  digitalWrite(Z_DIR_PIN, UP);
  while (z_pos < z_range)
  {
    digitalWrite(Z_STEP_PIN,1);
    delay(1);
    digitalWrite(Z_STEP_PIN,0);
    delay (1);
    z_pos++;
  }
  // GO TO X POSITION
  if (x < x_pos)
  {
    digitalWrite(X_DIR_PIN, DOWN);
    digitalWrite(E_DIR_PIN, UP);
    while (x_pos != x)
    {
      digitalWrite(X_STEP_PIN,1);
      digitalWrite(E_STEP_PIN,1);
      delay(1);
      digitalWrite(X_STEP_PIN,0);
      digitalWrite(E_STEP_PIN,0);
      delay(1);
      x_pos--;
    }
  }
  else if (x > x_pos)
  {
    digitalWrite(X_DIR_PIN, UP);
    digitalWrite(E_DIR_PIN, DOWN);
    while (x_pos != x)
    {
      digitalWrite(X_STEP_PIN,1);
      digitalWrite(E_STEP_PIN,1);
      delay(1);
      digitalWrite(X_STEP_PIN,0);
      digitalWrite(E_STEP_PIN,0);
      delay(1);
      x_pos++;
    }
  }

  // GO TO Y POSITION
  if (y < y_pos)
  {
    digitalWrite(Y_DIR_PIN, DOWN);
    while (y_pos != y)
    {
      digitalWrite(Y_STEP_PIN,1);
      delay(1);
      digitalWrite(Y_STEP_PIN,0);
      delay(1);
      y_pos--;
    }
  }
  else if (y > y_pos)
  {
    digitalWrite(Y_DIR_PIN, UP);
    while (y_pos != y)
    {
      digitalWrite(Y_STEP_PIN,1);
      delay(1);
      digitalWrite(Y_STEP_PIN,0);
      delay(1);
      y_pos++;
    }
  }

  // MOVE HEAD DOWN TO Z POSITION
  if (z < z_pos)
  {
    digitalWrite(Z_DIR_PIN, DOWN);
    while (z_pos != z)
    {
      digitalWrite(Z_STEP_PIN,1);
      delay(1);
      digitalWrite(Z_STEP_PIN,0);
      delay(1);
      z_pos--;
    }
  }

  return 0;
}

/*
This function moves 1 step in dir (<0 is down, >0 is up) in the x direction
*/
void stepX(int dir)
{
  if (dir < 0 && x_pos > 0)
  {
    digitalWrite(X_DIR_PIN, DOWN);
    digitalWrite(E_DIR_PIN, UP);
    digitalWrite(X_STEP_PIN,1);
    digitalWrite(E_STEP_PIN,1);
    delay(1);
    digitalWrite(X_STEP_PIN,0);
    digitalWrite(E_STEP_PIN,0);
    x_pos--;
  }
  else if (dir > 0 && x_pos < x_range)
  {
    digitalWrite(X_DIR_PIN, UP);
    digitalWrite(E_DIR_PIN, DOWN);
    digitalWrite(X_STEP_PIN,1);
    digitalWrite(E_STEP_PIN,1);
    delay(1);
    digitalWrite(X_STEP_PIN,0);
    digitalWrite(E_STEP_PIN,0);
    x_pos++;
  }
  else
  {
    return;
  }
}

/*
This function moves 1 step in dir (<0 is down, >0 is up) in the x direction
*/
void stepY(int dir)
{
  if (dir < 0 && y_pos > 0)
  {
    digitalWrite(Y_DIR_PIN, DOWN);
    digitalWrite(Y_STEP_PIN,1);
    delay(1);
    digitalWrite(Y_STEP_PIN,0);
    y_pos--;
  }
  else if (dir > 0 && y_pos < y_range)
  {
    digitalWrite(Y_DIR_PIN, UP);
    digitalWrite(Y_STEP_PIN,1);
    delay(1);
    digitalWrite(Y_STEP_PIN,0);
    y_pos++;
  }
  else
  {
    return;
  }
}

/*
This function moves 1 step in dir (<0 is down, >0 is up) in the x direction
*/
void stepZ(int dir)
{
  if (dir < 0 && z_pos > 0)
  {
    digitalWrite(Z_DIR_PIN, DOWN);
    digitalWrite(Z_STEP_PIN,1);
    delay(1);
    digitalWrite(Z_STEP_PIN,0);
    z_pos--;
  }
  else if (dir > 0 && z_pos < z_range)
  {
    digitalWrite(Z_DIR_PIN, UP);
    digitalWrite(Z_STEP_PIN,1);
    delay(1);
    digitalWrite(Z_STEP_PIN,0);
    z_pos++;
  }
  else
  {
    return;
  }
}

/*
Interrupt code for hitting endstops
*/
void endstopInterrupt(void)
{
  int i;
  
  if (digitalRead(X_MIN_PIN) == 1)
  {
    x_pos = 0;
    for (i = 0; i < 10; i++)
    {
      stepX(1);
    }
    x_pos = 0;
  }
  else if (digitalRead(X_MAX_PIN) == 1)
  {
    x_range = x_pos;
    for (i = 0; i < 10; i++)
    {
      stepX(-1);
    }
    x_range = x_pos;
  }
  else if (digitalRead(Y_MIN_PIN) == 1)
  {
    y_pos = 0;
    for (i = 0; i < 10; i++)
    {
      stepY(1);
    }
    y_pos = 0;
  }
  else if (digitalRead(Y_MAX_PIN) == 1)
  {
    y_range = y_pos;
    for (i = 0; i < 10; i++)
    {
      stepY(-1);
    }
    y_range = y_pos;
  }
  else if (digitalRead(Z_MIN_PIN) == 1)
  {
    z_pos = 0;
    for (i = 0; i < 10; i++)
    {
      stepZ(1);
    }
    z_pos = 0;
  }
  else if (digitalRead(Z_MAX_PIN) == 1)
  {
    z_range = z_pos;
    for (i = 0; i < 10; i++)
    {
      stepZ(-1);
    }
    z_range = z_pos;
  }
}








void buttonMove()
{
  int strafe /* X */, dir /* Y */, vert /* Z */;
  
  // LEFT AND RIGHT
  if (digitalRead(RIGHT) == 0)
  {
    strafe = 1;
  }
  else if (digitalRead(LEFT) == 0)
  {
    strafe = -1;
  }
  else
  {
    strafe = 0;
  }

  // FORWARDS AND BACKWARDS
  if (digitalRead(FORWARDS) == 0)
  {
    dir = 1;
  }
  else if (digitalRead(BACKWARDS) == 0)
  {
    dir = -1;
  }
  else
  {
    dir = 0;
  }

  // UP AND DOWN
  if (digitalRead(SKY) == 0)
  {
    vert = 1;
  }
  else if (digitalRead(FLOOR) == 0)
  {
    vert = -1;
  }
  else
  {
    vert = 0;
  }

  if (DEBUG)
  {
    Serial.print("Strafe = ");
    Serial.println(strafe);
    Serial.print("Dir= ");
    Serial.println(dir);
    Serial.print("Vert = ");
    Serial.println(vert);
    delay(1000);
  }

  stepX(strafe);
  stepY(dir);
  stepZ(vert);
  delay(1);
}
