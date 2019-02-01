#include "move.h"

int go(int x, int y, int z)
{
  if (x < 0 || y < 0 || z < 0 || x > x_range || y > y_range || z > z_range)
  {
    Serial.print("Given bad go command");
    return -1;
  }
  // MOVE HEAD HIGH
  setDir('z',POS);
  while (z_pos < z_range/4)
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
    setDir('x',NEG);
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
    setDir('x',POS);
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
    setDir('y',NEG);
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
    setDir('y',POS);
    while (y_pos != y)
    {
      digitalWrite(Y_STEP_PIN,1);
      delay(1);
      digitalWrite(Y_STEP_PIN,0);
      delay(1);
      y_pos++;
    }
  }

  // GO TO Z POSITION
  if (z < z_pos)
  {
    setDir('z',NEG);
    while (z_pos != z)
    {
      digitalWrite(Z_STEP_PIN,1);
      delay(1);
      digitalWrite(Z_STEP_PIN,0);
      delay(1);
      z_pos--;
    }
  }
  else if (z > z_pos)
  {
    setDir('z',POS);
    while (z_pos != z)
    {
      digitalWrite(Z_STEP_PIN,1);
      delay(1);
      digitalWrite(Z_STEP_PIN,0);
      delay(1);
      z_pos++;
    }
  }
  return 0;
}

void stepX(int dir)
{
  if (dir < 0 && x_pos > 0)
  {
    setDir('x',NEG);
    digitalWrite(X_STEP_PIN,1);
    digitalWrite(E_STEP_PIN,1);
    delay(1);
    digitalWrite(X_STEP_PIN,0);
    digitalWrite(E_STEP_PIN,0);
    x_pos--;
  }
  else if (dir > 0 && x_pos < x_range)
  {
    setDir('x',POS);
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

void stepY(int dir)
{
  if (dir < 0 && y_pos > 0)
  {
    setDir('y',NEG);
    digitalWrite(Y_STEP_PIN,1);
    delay(1);
    digitalWrite(Y_STEP_PIN,0);
    y_pos--;
  }
  else if (dir > 0 && y_pos < y_range)
  {
    setDir('y',POS);
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
This function moves 1 step in dir (<0 is LOW, >0 is HIGH) in the x direction
*/
void stepZ(int dir)
{
  if (dir < 0 && z_pos > 0)
  {
    setDir('z',NEG);
    digitalWrite(Z_STEP_PIN,1);
    delay(1);
    digitalWrite(Z_STEP_PIN,0);
    z_pos--;
  }
  else if (dir > 0 && z_pos < z_range)
  {
    setDir('z',POS);
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
InterrHIGHt code for hitting endstops
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

  // HIGH AND LOW
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

void setDir(char axis, int dir)
{
  switch (axis)
  {
    case 'x':
      if (dir < 0)
      {
        digitalWrite(X_DIR_PIN, LOW);
        digitalWrite(E_DIR_PIN, HIGH);
      }
      else if (dir > 0)
      {
        digitalWrite(X_DIR_PIN, HIGH);
        digitalWrite(E_DIR_PIN, LOW);
      }
      break;
    case 'y':
      if (dir < 0)
      {
        digitalWrite(Y_DIR_PIN, LOW);
      }
      else if (dir > 0)
      {
        digitalWrite(Y_DIR_PIN, HIGH);
      }
      break;
    case 'z':
      if (dir < 0)
      {
        digitalWrite(Z_DIR_PIN, HIGH);
      }
      else if (dir > 0)
      {
        digitalWrite(Z_DIR_PIN, LOW);
      }
      break;
    default:
      break;
  }
}
