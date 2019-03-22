#include "move.h"

int move(char axis, int dir, int num_steps)
{
	float * del;
	int inc;
	int i,j;

	inc = (dir < 0)?(-1):(1);
	del = (float *)malloc(num_steps*sizeof(float));
	if (del == NULL)
	{
		Serial.println("Error allocating delays in move.cpp:move");
		return 0;
	}

	// Return if number of steps is 0 (should never be less than 0)
	if (num_steps <= 0)
	{
		free(del);
		return 0;
	}

	setDir(axis,dir);
	
	#define START_DELAY 50
	#define LAST_DELAY 1
	#define ACCEL 1.1
	#define NUM_RAMP 43
	
	// if not enough steps for full ramp...
	if (num_steps < 2*NUM_RAMP)
	{
		del[0] = START_DELAY;
		for (i = 1; i < num_steps/2; i++)
		{
			del[i] = del[i-1]/ACCEL;
		}
		for (; i < num_steps; i++)
		{
			del[i] = del[i-1]*ACCEL;
		}
	}
	// if there are enough for full ramp
	else
	{
		del[0] = START_DELAY;
		for (i = 1; i < NUM_RAMP; i++)
		{
			del[i] = del[i-1]/ACCEL;
		}
		for (; i < num_steps-NUM_RAMP; i++)
		{
			del[i] = 1;
		}
		j = 0;
		for (; i < num_steps; i++)
		{
			del[i] = 2*(NUM_RAMP-j+1);
			j++;
		}
	}
	
	// STEP
	if (axis == 'x')
	{
		for (i = 0; i < num_steps; i++)
		{
			digitalWrite(X_STEP_PIN,HIGH);
			delay(static_cast<int>(del[i]));
			digitalWrite(X_STEP_PIN,LOW);
			delay(static_cast<int>(del[i]));
			x_pos += inc;
		}
	}
	else if (axis == 'y')
	{
		for (i = 0; i < num_steps; i++)
		{
			digitalWrite(Y_STEP_PIN,HIGH);
			digitalWrite(E_STEP_PIN,HIGH);
			delay(static_cast<int>(del[i]));
			digitalWrite(Y_STEP_PIN,LOW);
			digitalWrite(E_STEP_PIN,LOW);
			delay(static_cast<int>(del[i]));
			y_pos += inc;
		}
	}
	else if (axis == 'z')
	{
		for (i = 0; i < num_steps; i++)
		{
			digitalWrite(Z_STEP_PIN,HIGH);
			delay(static_cast<int>(del[i]));
			digitalWrite(Z_STEP_PIN,LOW);
			delay(static_cast<int>(del[i]));
			z_pos += inc;
		}
	}

	free(del);
	
	return 0;
}


int go(int x, int y, int z)
{
  if (x < 0 || y < 0 || z < 0 || x > x_range || y > y_range || z > z_range)
  {
    Serial.print("Given bad go command");
    return -1;
  }
  // MOVE HEAD HIGH
  move('z', POS, (z_pos<z_range/4)?(z_range/4-z_pos):(0));
  
  // GO TO X POSITION
  move('x', (x<x_pos)?(NEG):(POS), abs(x-x_pos));

  // GO TO Y POSITION
  move('y', (y<y_pos)?(NEG):(POS), abs(y-y_pos));

  // GO TO Z POSITION
  move('z', (z<z_pos)?(NEG):(POS), abs(z-z_pos));
  
  return 0;
}

void endstopInterrupt(void)
{
  if (digitalRead(X_MIN_PIN) == 1)
  {
    x_pos = 0;
    move('x', POS, 10);
    x_pos = 0;
  }
  else if (digitalRead(X_MAX_PIN) == 1)
  {
    x_range = x_pos;
    move('x', NEG, 10);
    x_range = x_pos;
  }
  else if (digitalRead(Y_MIN_PIN) == 1)
  {
    y_pos = 0;
    move('y', POS, 10);
    y_pos = 0;
  }
  else if (digitalRead(Y_MAX_PIN) == 1)
  {
    y_range = y_pos;
    move('y', NEG, 10);
    y_range = y_pos;
  }
  else if (digitalRead(Z_MIN_PIN) == 1)
  {
    z_pos = 0;
    move('z', POS, 10);
    z_pos = 0;
  }
  else if (digitalRead(Z_MAX_PIN) == 1)
  {
    z_range = z_pos;
    move('z', NEG, 10);
    z_range = z_pos;
  }
}








void buttonMove()
{
  int x, y, z;
  
  // LEFT AND RIGHT
  if (digitalRead(X_P) == 0)
  {
    x = 1;
  }
  else if (digitalRead(X_N) == 0)
  {
    x = -1;
  }
  else
  {
    x = 0;
  }

  // FORWARDS AND BACKWARDS
  if (digitalRead(Y_P) == 0)
  {
    y = 1;
  }
  else if (digitalRead(Y_N) == 0)
  {
    y = -1;
  }
  else
  {
    y = 0;
  }

  // HIGH AND LOW
  if (digitalRead(Z_P) == 0)
  {
    z = 1;
  }
  else if (digitalRead(Z_N) == 0)
  {
    z = -1;
  }
  else
  {
    z = 0;
  }

  if (DEBUG)
  {
    Serial.print("X = ");
    Serial.println(x);
    Serial.print("Y = ");
    Serial.println(y);
    Serial.print("Z = ");
    Serial.println(z);
    delay(1000);
  }

  move('x', (x<0)?(NEG):(POS), 1);
  move('y', (y<0)?(NEG):(POS), 1);
  move('z', (z<0)?(NEG):(POS), 1);
}

void setDir(char axis, int dir)
{
  switch (axis)
  {
    case 'x':
      if (dir < 0)
      {
        digitalWrite(X_DIR_PIN, LOW);
      }
      else if (dir > 0)
      {
        digitalWrite(X_DIR_PIN, HIGH);
      }
      break;
    case 'y':
      if (dir < 0)
      {
        digitalWrite(Y_DIR_PIN, LOW);
        digitalWrite(E_DIR_PIN, HIGH);
      }
      else if (dir > 0)
      {
        digitalWrite(Y_DIR_PIN, HIGH);
        digitalWrite(E_DIR_PIN, LOW);
      }
      break;
    case 'z':
      if (dir < 0)
      {
        digitalWrite(Z_DIR_PIN, LOW);
      }
      else if (dir > 0)
      {
        digitalWrite(Z_DIR_PIN, HIGH);
      }
      break;
    default:
      break;
  }
}

void vacuum(char state)
{
	if (state == ON)
	{
		digitalWrite(VACUUM_PIN,HIGH);
	}
	else
	{
		digitalWrite(VACUUM_PIN,LOW);
	}
}
