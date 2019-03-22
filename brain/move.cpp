#include "move.h"

int move(char axis, int dir, int num_steps)
{
	int step_pin, step_pin2;
	int * loc;
	char * del;
	int i,j;
	
	inc = (dir < 0)?(-1):(1);
	del = (char *)malloc(num_steps*sizeof(char));
	
	// Return if number of steps is 0 (should never be less than 0)
	if (num_steps <= 0)
	{
		return 0;
	}
	
	setDir(axis,dir);
	
	// set axis
	switch (axis)
	{
		case 'x':
			step_pin = X_STEP_PIN;
			loc = &x_pos;
			break;
		case 'y':
			step_pin = Y_STEP_PIN;
			step_pin2 = E_STEP_PIN;
			loc = &y_pos;
			break;
		case 'z':
			step_pin = Z_STEP_PIN;
			loc = &z_pos;
			break;
		default:
			return 1;
	}
	
	// if not enough steps for full ramp...
	if (num_steps < 2*NUM_RAMP)
	{
		for (i = 0; i < num_steps/2; i++)
		{
			del[i] = 2*(NUM_RAMP-i+1);
		}
		for (; i < num_steps; i++)
		{
			del[i] = del[i-1]-2;
		}
	}
	// if there are enough for full ramp
	else
	{
		for (i = 0; i < NUM_RAMP; i++)
		{
			del[i] = 2*(NUM_RAMP-i+1);
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
	if (axis == 'y')
	{
		for (i = 0; i < num_steps; i++)
		{
			digitalWrite(step_pin,HIGH);
			delay(del[i]);
			digitalWrite(step_pin,LOW);
			delay(del[i]);
			*loc += inc;
		}
	}
	else
	{
		for (i = 0; i < num_steps; i++)
		{
			digitalWrite(step_pin,HIGH);
			digitalWrite(step_pin2,HIGH);
			delay(del[i]);
			digitalWrite(step_pin,LOW);
			digitalWrite(step_pin2,LOW);
			delay(del[i]);
			*loc += inc;
		}
	}
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
  int i;
  
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