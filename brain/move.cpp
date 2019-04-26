#include "move.h"

int move(char axis, int dir, int num_steps)
{
	float del[2*NUM_RAMP];
	int inc;
	int i,j;

	inc = (dir < 0)?(-1):(1);

	// Return if number of steps is 0 (should never be less than 0)
	if (num_steps <= 0)
	{
		return 0;
	}

	setDir(axis,dir);

	// SETUP RAMP
	del[0] = START_DELAY;
	for (i = 1; i < num_steps/2 && i < NUM_RAMP; i++)
	{
		del[i] = del[i-1]/(float)ACCEL;
	}
	for (; i < num_steps && i < NUM_RAMP*2; i++)
	{
		del[i] = del[i-1]*ACCEL;
	}

	// STEP
	j = 0;
	if (axis == 'x')
	{
		// RAMP UP
		for (i = 0; i < num_steps/2 && i < NUM_RAMP; i++)
		{
			digitalWrite(X_STEP_PIN,HIGH);
			delayMicroseconds(static_cast<int>(del[j]));
			digitalWrite(X_STEP_PIN,LOW);
			delayMicroseconds(static_cast<int>(del[j]));
			x_pos += inc;
			j++;
		}
		// FULL SPEED
		for (; i < num_steps - NUM_RAMP; i++)
		{
			digitalWrite(X_STEP_PIN,HIGH);
			delayMicroseconds(MIN_DELAY);
			digitalWrite(X_STEP_PIN,LOW);
			delayMicroseconds(MIN_DELAY);
			x_pos += inc;
		}
		// RAMP DOWN
		for (; i < num_steps; i++)
		{
			digitalWrite(X_STEP_PIN,HIGH);
			delayMicroseconds(static_cast<int>(del[j]));
			digitalWrite(X_STEP_PIN,LOW);
			delayMicroseconds(static_cast<int>(del[j]));
			x_pos += inc;
			j++;
		}
	}
	else if (axis == 'y')
	{
		// RAMP UP
		for (i = 0; i < num_steps/2 && i < NUM_RAMP; i++)
		{
			digitalWrite(Y_STEP_PIN,HIGH);
			digitalWrite(E_STEP_PIN,HIGH);
			delayMicroseconds(static_cast<int>(del[j]));
			digitalWrite(Y_STEP_PIN,LOW);
			digitalWrite(E_STEP_PIN,LOW);
			delayMicroseconds(static_cast<int>(del[j]));
			y_pos += inc;
			j++;
		}
		// FULL SPEED
		for (; i < num_steps - NUM_RAMP; i++)
		{
			digitalWrite(Y_STEP_PIN,HIGH);
			digitalWrite(E_STEP_PIN,HIGH);
			delayMicroseconds(MIN_DELAY);
			digitalWrite(Y_STEP_PIN,LOW);
			digitalWrite(E_STEP_PIN,LOW);
			delayMicroseconds(MIN_DELAY);
			y_pos += inc;
		}
		// RAMP DOWN
		for (; i < num_steps; i++)
		{
			digitalWrite(Y_STEP_PIN,HIGH);
			digitalWrite(E_STEP_PIN,HIGH);
			delayMicroseconds(static_cast<int>(del[j]));
			digitalWrite(Y_STEP_PIN,LOW);
			digitalWrite(E_STEP_PIN,LOW);
			delayMicroseconds(static_cast<int>(del[j]));
			y_pos += inc;
			j++;
		}
	}
	else if (axis == 'z')
	{
		// RAMP UP
		for (i = 0; i < num_steps/2 && i < NUM_RAMP; i++)
		{
			digitalWrite(Z_STEP_PIN,HIGH);
			delayMicroseconds(static_cast<int>(del[j]));
			digitalWrite(Z_STEP_PIN,LOW);
			delayMicroseconds(static_cast<int>(del[j]));
			z_pos += inc;
			j++;
		}
		// FULL SPEED
		for (; i < num_steps - NUM_RAMP; i++)
		{
			digitalWrite(Z_STEP_PIN,HIGH);
			delayMicroseconds(MIN_DELAY);
			digitalWrite(Z_STEP_PIN,LOW);
			delayMicroseconds(MIN_DELAY);
			z_pos += inc;
		}
		// RAMP DOWN
		for (; i < num_steps; i++)
		{
			digitalWrite(Z_STEP_PIN,HIGH);
			delayMicroseconds(static_cast<int>(del[j]));
			digitalWrite(Z_STEP_PIN,LOW);
			delayMicroseconds(static_cast<int>(del[j]));
			z_pos += inc;
			j++;
		}
	}

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
    move('x', POS, SAFETY);
    x_pos = 0;
  }
  else if (digitalRead(X_MAX_PIN) == 1)
  {
    x_range = x_pos;
    move('x', NEG, SAFETY);
    x_range = x_pos;
  }
  else if (digitalRead(Y_MIN_PIN) == 1)
  {
    y_pos = 0;
    move('y', POS, SAFETY);
    y_pos = 0;
  }
  else if (digitalRead(Y_MAX_PIN) == 1)
  {
    y_range = y_pos;
    move('y', NEG, SAFETY);
    y_range = y_pos;
  }
  else if (digitalRead(Z_MIN_PIN) == 1)
  {
    z_pos = 0;
    move('z', POS, SAFETY);
    z_pos = 0;
  }
  else if (digitalRead(Z_MAX_PIN) == 1)
  {
    z_range = z_pos;
    move('z', NEG, SAFETY);
    z_range = z_pos;
  }
}


void buttonMove()
{
  char x, y, z;
  char v, p;

  // LEFT AND RIGHT
  if (digitalRead(X_P) == 0)
  {
    x = POS;
  }
  else if (digitalRead(X_N) == 0)
  {
    x = NEG;
  }
  else
  {
    x = 0;
  }

  // FORWARDS AND BACKWARDS
  if (digitalRead(Y_P) == 0)
  {
    y = POS;
  }
  else if (digitalRead(Y_N) == 0)
  {
    y = NEG;
  }
  else
  {
    y = 0;
  }

  // HIGH AND LOW
  if (digitalRead(Z_P) == 0)
  {
    z = POS;
  }
  else if (digitalRead(Z_N) == 0)
  {
    z = NEG;
  }
  else
  {
    z = 0;
  }

  if (digitalRead(P_1) == 0)
  {
    v = ON;
  }
  else
  {
    v = OFF;
  }

  if (digitalRead(P_2) == 0)
  {
    p = ON;
  }
  else
  {
    p = OFF;
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

  move('x', x, (x==0)?(0):1);
  move('y', y, (y==0)?(0):1);
  move('z', z, (z==0)?(0):1);

  vacuum(v);
  pump(p);
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

void pump(char state)
{
	if (state == ON)
	{
		digitalWrite(PUMP_PIN,HIGH);
	}
	else
	{
		digitalWrite(PUMP_PIN,LOW);
	}
}
