#include "init.h"

void setupPins(void)
{
  // Set HIGH pin modes
  pinMode(FAN_PIN , OUTPUT);
  pinMode(VACUUM_PIN , OUTPUT);
  pinMode(HEATER_1_PIN , OUTPUT);
  pinMode(LED_PIN  , OUTPUT);

  pinMode(X_STEP_PIN  , OUTPUT);
  pinMode(X_DIR_PIN    , OUTPUT);
  pinMode(X_ENABLE_PIN    , OUTPUT);

  pinMode(Y_STEP_PIN  , OUTPUT);
  pinMode(Y_DIR_PIN    , OUTPUT);
  pinMode(Y_ENABLE_PIN    , OUTPUT);

  pinMode(Z_STEP_PIN  , OUTPUT);
  pinMode(Z_DIR_PIN    , OUTPUT);
  pinMode(Z_ENABLE_PIN    , OUTPUT);

  pinMode(E_STEP_PIN  , OUTPUT);
  pinMode(E_DIR_PIN    , OUTPUT);
  pinMode(E_ENABLE_PIN    , OUTPUT);


	pinMode(Z_MIN_PIN,INPUT);
	pinMode(Z_MAX_PIN,INPUT);
	pinMode(Y_MIN_PIN,INPUT);
	pinMode(Y_MAX_PIN,INPUT);
	pinMode(X_MAX_PIN,INPUT);
	pinMode(X_MIN_PIN,INPUT);

  digitalWrite(X_ENABLE_PIN    , LOW);
  digitalWrite(Y_ENABLE_PIN    , LOW);
  digitalWrite(Z_ENABLE_PIN    , LOW);
  digitalWrite(E_ENABLE_PIN    , LOW);

  pinMode(PUMP_PIN, OUTPUT);
  digitalWrite(PUMP_PIN, LOW);

  // Controller Setup
  pinMode(X_P,INPUT_PULLUP);
  pinMode(X_N,INPUT_PULLUP);
  pinMode(Y_P,INPUT_PULLUP);
  pinMode(Y_N,INPUT_PULLUP);
  pinMode(Z_P,INPUT_PULLUP);
  pinMode(Z_N,INPUT_PULLUP);
  pinMode(P_1,INPUT_PULLUP);
  pinMode(P_2,INPUT_PULLUP);
}

void initInterrupts()
{
	/* NOTE Y_MAX AND Z_MIN NOT CONNECTED TO INTERRUPTS */
	/* reference arduino documentation and ramps pinout for interrupt numbers */
	
  // interrupts
  attachInterrupt(1, endstopInterrupt, CHANGE); // X_MIN_PIN
  attachInterrupt(0, endstopInterrupt, CHANGE); // X_MAX_PIN
  attachInterrupt(5, endstopInterrupt, CHANGE); // Y_MIN_PIN
  //attachInterrupt(, endstopInterrupt, CHANGE); // Y_MAX_PIN
  //attachInterrupt(, endstopInterrupt, CHANGE); // Z_MIN_PIN
  attachInterrupt(4, endstopInterrupt, CHANGE); // Z_MAK_PIN
}

/*
This function moves the machine to the min x, min y, and max z
then sets the limits and positions to what they should be
(assumes nothing moves)
*/
void zero()
{
	int i;

	// FIND MAXIMUM OF Z-AXIS
	setDir('z', POS);
	i = 0;
	while (digitalRead(Z_MAX_PIN) == 1)
	{
		digitalWrite(Z_STEP_PIN,1);
		delay(1);
		digitalWrite(Z_STEP_PIN,0);
		delay(1);
	}
	// GO SLOW
	setDir('z', NEG);
	for (i = 0; i < SAFETY; i++)
	{
		digitalWrite(Z_STEP_PIN,1);
		delay(2);
		digitalWrite(Z_STEP_PIN,0);
		delay(2);
	}
	delay(500);
	setDir('z', POS);
	while (digitalRead(Z_MAX_PIN) == 1)
	{
		digitalWrite(Z_STEP_PIN,1);
		delay(4);
		digitalWrite(Z_STEP_PIN,0);
		delay(4);
	}
	delay(500);
	z_range -= 2*SAFETY;
	
	// FIND MINIMUM OF X-AXIS
	setDir('x', NEG);
	i = 0;
	while (digitalRead(X_MIN_PIN) == 1)
	{
		digitalWrite(X_STEP_PIN,1);
		delay(1);
		digitalWrite(X_STEP_PIN,0);
		delay(1);
	}
	// GO SLOW
	setDir('x', POS);
	for (i = 0; i < SAFETY; i++)
	{
		digitalWrite(X_STEP_PIN,1);
		delay(2);
		digitalWrite(X_STEP_PIN,0);
		delay(2);
	}
	delay(500);
	setDir('x', NEG);
	while (digitalRead(X_MIN_PIN) == 1)
	{
		digitalWrite(X_STEP_PIN,1);
		delay(4);
		digitalWrite(X_STEP_PIN,0);
		delay(4);
	}
	delay(500);
	
	// FIND MINIMUM OF Y-AXIS
	setDir('y', NEG);
	i = 0;
	while (digitalRead(Y_MIN_PIN) == 1)
	{
		digitalWrite(Y_STEP_PIN,1);
		digitalWrite(E_STEP_PIN,1);
		delay(1);
		digitalWrite(Y_STEP_PIN,0);
		digitalWrite(E_STEP_PIN,0);
		delay(1);
	}
	// GO SLOW
	setDir('y', POS);
	for (i = 0; i < SAFETY; i++)
	{
		digitalWrite(Y_STEP_PIN,1);
		digitalWrite(E_STEP_PIN,1);
		delay(2);
		digitalWrite(Y_STEP_PIN,0);
		digitalWrite(E_STEP_PIN,0);
		delay(2);
	}
	delay(500);
	setDir('y', NEG);
	while (digitalRead(Y_MIN_PIN) == 1)
	{
		digitalWrite(Y_STEP_PIN,1);
		digitalWrite(E_STEP_PIN,1);
		delay(4);
		digitalWrite(Y_STEP_PIN,0);
		digitalWrite(E_STEP_PIN,0);
		delay(4);
	}
	delay(500);
	
	
	x_range = 3342-2*SAFETY;
	y_range = 8011-2*SAFETY;
	z_range = 6587-2*SAFETY;
	
	x_pos = -SAFETY;
	y_pos = -SAFETY;
	z_pos = z_range+SAFETY;
}

/*
This function calibrates the endpoints of the machine
It provides a safety margin of SAFETY steps
Goes from x-min to x-max, y-min to y-max, then z-min to z-max.
*/
void calibrate()
{
  int i;

  // FIND MINIMUM OF Z-AXIS
  setDir('z',NEG);
  while (digitalRead(Z_MIN_PIN) == 1)
  {
    digitalWrite(Z_STEP_PIN,1);
    delay(1);
    digitalWrite(Z_STEP_PIN,0);
    delay(1);
  }
  setDir('z',POS);
  for (i = 0; i < SAFETY; i++)
  {
    digitalWrite(Z_STEP_PIN,1);
    delay(1);
    digitalWrite(Z_STEP_PIN,0);
    delay(1);
  }

  // FIND MAXIMUM OF Z-AXIS
  setDir('z',POS);
  while (digitalRead(Z_MAX_PIN) == 1)
  {
    digitalWrite(Z_STEP_PIN,1);
    delay(1);
    digitalWrite(Z_STEP_PIN,0);
    delay(1);
    z_range++;
  }
  setDir('z',NEG);
  for (i = 0; i < SAFETY; i++)
  {
    digitalWrite(Z_STEP_PIN,1);
    delay(1);
    digitalWrite(Z_STEP_PIN,0);
    delay(1);
    z_range--;
  }
  
  // FIND MINIMUM OF X-AXIS
  setDir('x',NEG);
  while (digitalRead(X_MIN_PIN) == 1)
  {
    digitalWrite(X_STEP_PIN,1);
    delay(1);
    digitalWrite(X_STEP_PIN,0);
    delay(1);
  }
  setDir('x',POS);
  for (i = 0; i < SAFETY; i++)
  {
    digitalWrite(X_STEP_PIN,1);
    delay(1);
    digitalWrite(X_STEP_PIN,0);
    delay(1);
  }

  // FIND MAXIMUM OF X-AXIS
  setDir('x',POS);
  while (digitalRead(X_MAX_PIN) == 1)
  {
    digitalWrite(X_STEP_PIN,1);
    delay(1);
    digitalWrite(X_STEP_PIN,0);
    delay(1);
    x_range++;
  }
  setDir('x',NEG);
  for (i = 0; i < SAFETY; i++)
  {
    digitalWrite(X_STEP_PIN,1);
    delay(1);
    digitalWrite(X_STEP_PIN,0);
    delay(1);
    x_range--;
  }
  
  // FIND MINIMUM OF Y-AXIS
  setDir('y',NEG);
  while (digitalRead(Y_MIN_PIN) == 1)
  {
    digitalWrite(Y_STEP_PIN,1);
	digitalWrite(E_STEP_PIN,1);
    delay(1);
    digitalWrite(Y_STEP_PIN,0);
	digitalWrite(E_STEP_PIN,0);
    delay(1);
  }
  setDir('y',POS);
  for (i = 0; i < SAFETY; i++)
  {
    digitalWrite(Y_STEP_PIN,1);
	digitalWrite(E_STEP_PIN,1);
    delay(1);
    digitalWrite(Y_STEP_PIN,0);
	digitalWrite(E_STEP_PIN,0);
    delay(1);
  }
  
  // FIND MAXIMUM OF Y-AXIS
  setDir('y',POS);
  while (digitalRead(Y_MAX_PIN) == 1)
  {
    digitalWrite(Y_STEP_PIN,1);
	digitalWrite(E_STEP_PIN,1);
    delay(1);
    digitalWrite(Y_STEP_PIN,0);
	digitalWrite(E_STEP_PIN,0);
    delay(1);
    y_range++;
  }
  setDir('y',NEG);
  for (i = 0; i < SAFETY; i++)
  {
    digitalWrite(Y_STEP_PIN,1);
	digitalWrite(E_STEP_PIN,1);
    delay(1);
    digitalWrite(Y_STEP_PIN,0);
	digitalWrite(E_STEP_PIN,0);
    delay(1);
    y_range--;
  }

  x_pos = x_range;
  y_pos = y_range;
  z_pos = z_range;
}

/*
int calibrate()
{
  int i;
  float del[NUM_RAMP_INIT];
  float delS[SAFETY];
  
  
  // Initialize del
  del[0] = START_DELAY_INIT;
  for (i = 1; i < NUM_RAMP_INIT; i++)
  {
	del[i] = del[i-1]/(float)ACCEL_INIT;
  }
  // Initialize delS
  delS[0] = START_DELAY_INIT;
  for (i = 1; i < SAFETY/2 && i < NUM_RAMP_INIT; i++) 
  {
	delS[i] = delS[i-1]/(float)ACCEL_INIT;
  }
  for (; i < SAFETY; i++) // trying no ramp down
  {
  	delS[i] = MIN_DELAY;
  }
  for (; i < SAFETY; i++)
  {
  	delS[i] = delS[i-1]*ACCEL_INIT;
  }
  
	// FIND MAXIMUM OF Z-AXIS
	setDir('z', POS);
	i = 0;
	while (digitalRead(Z_MAX_PIN) == 1)
	{
		if (i < NUM_RAMP_INIT)
		{
			digitalWrite(Z_STEP_PIN,1);
			delayMicroseconds(static_cast<int>(del[i]));
			digitalWrite(Z_STEP_PIN,1);
			delayMicroseconds(static_cast<int>(del[i]));
			i++;
		}
		else
		{
		digitalWrite(Z_STEP_PIN,1);
		delayMicroseconds(MIN_DELAY);
		digitalWrite(Z_STEP_PIN,0);
		delayMicroseconds(MIN_DELAY);
		}
	}
	
	
	// FIND MINIMUM OF X-AXIS
	setDir('x', NEG);
	i = 0;
	while (digitalRead(X_MIN_PIN) == 1)
	{
		if (i < NUM_RAMP_INIT)
		{
			digitalWrite(X_STEP_PIN,1);
			delayMicroseconds(static_cast<int>(del[i]));
			digitalWrite(X_STEP_PIN,1);
			delayMicroseconds(static_cast<int>(del[i]));
			i++;
		}
		else
		{
		digitalWrite(X_STEP_PIN,1);
		delayMicroseconds(MIN_DELAY);
		digitalWrite(X_STEP_PIN,0);
		delayMicroseconds(MIN_DELAY);
		}
	}
	// GO SLOW
	setDir('x', POS);
	for (i = 0; i < SAFETY; i++)
	{
		digitalWrite(X_STEP_PIN,1);
		delay(2);
		digitalWrite(X_STEP_PIN,0);
		delay(2);
	}
	delay(500);
	setDir('x', NEG);
	while (digitalRead(X_MIN_PIN) == 1)
	{
		digitalWrite(X_STEP_PIN,1);
		delay(4);
		digitalWrite(X_STEP_PIN,0);
		delay(4);
	}
	delay(500);
	
	// FIND MAXIMUM OF X-AXIS
	setDir('x', POS);
	i = 0;
	while (digitalRead(X_MAX_PIN) == 1)
	{
		if (i < NUM_RAMP_INIT)
		{
			digitalWrite(X_STEP_PIN,1);
			delayMicroseconds(static_cast<int>(del[i]));
			digitalWrite(X_STEP_PIN,1);
			delayMicroseconds(static_cast<int>(del[i]));
			i++;
			x_range++;
		}
		else
		{
		digitalWrite(X_STEP_PIN,1);
		delayMicroseconds(MIN_DELAY);
		digitalWrite(X_STEP_PIN,0);
		delayMicroseconds(MIN_DELAY);
			x_range++;
		}
	}
	// GO SLOW
	setDir('x', NEG);
	for (i = 0; i < SAFETY; i++)
	{
		digitalWrite(X_STEP_PIN,1);
		delay(2);
		digitalWrite(X_STEP_PIN,0);
		delay(2);
		x_range--;
	}
	delay(500);
	setDir('x', POS);
	while (digitalRead(X_MAX_PIN) == 1)
	{
		digitalWrite(X_STEP_PIN,1);
		delay(4);
		digitalWrite(X_STEP_PIN,0);
		delay(4);
		x_range++;
	}
	delay(500);
	x_range -= 2*SAFETY;
	
	
	// FIND MINIMUM OF Y-AXIS
	setDir('y', NEG);
	i = 0;
	while (digitalRead(Y_MIN_PIN) == 1)
	{
		if (i < NUM_RAMP_INIT)
		{
			digitalWrite(Y_STEP_PIN,1);
			digitalWrite(E_STEP_PIN,1);
			delayMicroseconds(static_cast<int>(del[i]));
			digitalWrite(Y_STEP_PIN,1);
			digitalWrite(E_STEP_PIN,1);
			delayMicroseconds(static_cast<int>(del[i]));
			i++;
		}
		else
		{
		digitalWrite(Y_STEP_PIN,1);
		digitalWrite(E_STEP_PIN,1);
		delayMicroseconds(MIN_DELAY);
		digitalWrite(Y_STEP_PIN,0);
		digitalWrite(E_STEP_PIN,0);
		delayMicroseconds(MIN_DELAY);
		}
	}
	// GO SLOW
	setDir('y', POS);
	for (i = 0; i < SAFETY; i++)
	{
		digitalWrite(Y_STEP_PIN,1);
		digitalWrite(E_STEP_PIN,1);
		delay(2);
		digitalWrite(Y_STEP_PIN,0);
		digitalWrite(E_STEP_PIN,0);
		delay(2);
	}
	delay(500);
	setDir('y', NEG);
	while (digitalRead(Y_MIN_PIN) == 1)
	{
		digitalWrite(Y_STEP_PIN,1);
		digitalWrite(E_STEP_PIN,1);
		delay(4);
		digitalWrite(Y_STEP_PIN,0);
		digitalWrite(E_STEP_PIN,0);
		delay(4);
	}
	delay(500);
	
	// FIND MAXIMUM OF Y-AXIS
	setDir('y', POS);
	i = 0;
	while (digitalRead(Y_MAX_PIN) == 1)
	{
		if (i < NUM_RAMP_INIT)
		{
			digitalWrite(Y_STEP_PIN,1);
			digitalWrite(E_STEP_PIN,1);
			delayMicroseconds(static_cast<int>(del[i]));
			digitalWrite(Y_STEP_PIN,1);
			digitalWrite(E_STEP_PIN,1);
			delayMicroseconds(static_cast<int>(del[i]));
			i++;
			y_range++;
		}
		else
		{
		digitalWrite(Y_STEP_PIN,1);
		digitalWrite(E_STEP_PIN,1);
		delayMicroseconds(MIN_DELAY);
		digitalWrite(Y_STEP_PIN,0);
		digitalWrite(E_STEP_PIN,0);
		delayMicroseconds(MIN_DELAY);
			y_range++;
		}
	}
	// GO SLOW
	setDir('y', NEG);
	for (i = 0; i < SAFETY; i++)
	{
		digitalWrite(Y_STEP_PIN,1);
		digitalWrite(E_STEP_PIN,1);
		delay(2);
		digitalWrite(Y_STEP_PIN,0);
		digitalWrite(E_STEP_PIN,0);
		delay(2);
		y_range--;
	}
	delay(500);
	setDir('y', POS);
	while (digitalRead(Y_MAX_PIN) == 1)
	{
		digitalWrite(Y_STEP_PIN,1);
		digitalWrite(E_STEP_PIN,1);
		delay(4);
		digitalWrite(Y_STEP_PIN,0);
		digitalWrite(E_STEP_PIN,0);
		delay(4);
		y_range++;
	}
	delay(500);
	y_range -= 2*SAFETY;
	
	
	// FIND MINIMUM OF Z-AXIS
	setDir('z', NEG);
	i = 0;
	while (digitalRead(Z_MIN_PIN) == 1)
	{
		if (i < NUM_RAMP_INIT)
		{
			digitalWrite(Z_STEP_PIN,1);
			delayMicroseconds(static_cast<int>(del[i]));
			digitalWrite(Z_STEP_PIN,1);
			delayMicroseconds(static_cast<int>(del[i]));
			i++;
		}
		else
		{
		digitalWrite(Z_STEP_PIN,1);
		delayMicroseconds(MIN_DELAY);
		digitalWrite(Z_STEP_PIN,0);
		delayMicroseconds(MIN_DELAY);
		}
	}
	// GO SLOW
	setDir('z', POS);
	for (i = 0; i < SAFETY; i++)
	{
		digitalWrite(Z_STEP_PIN,1);
		delay(2);
		digitalWrite(Z_STEP_PIN,0);
		delay(2);
	}
	delay(500);
	setDir('z', NEG);
	while (digitalRead(Z_MIN_PIN) == 1)
	{
		digitalWrite(Z_STEP_PIN,1);
		delay(4);
		digitalWrite(Z_STEP_PIN,0);
		delay(4);
	}
	delay(500);
	
	// FIND MAXIMUM OF Z-AXIS
	setDir('z', POS);
	i = 0;
	while (digitalRead(Z_MAX_PIN) == 1)
	{
		if (i < NUM_RAMP_INIT)
		{
			digitalWrite(Z_STEP_PIN,1);
			delayMicroseconds(static_cast<int>(del[i]));
			digitalWrite(Z_STEP_PIN,1);
			delayMicroseconds(static_cast<int>(del[i]));
			i++;
			z_range++;
		}
		else
		{
		digitalWrite(Z_STEP_PIN,1);
		delayMicroseconds(MIN_DELAY);
		digitalWrite(Z_STEP_PIN,0);
		delayMicroseconds(MIN_DELAY);
			z_range++;
		}
	}
	// GO SLOW
	setDir('z', NEG);
	for (i = 0; i < SAFETY; i++)
	{
		digitalWrite(Z_STEP_PIN,1);
		delay(2);
		digitalWrite(Z_STEP_PIN,0);
		delay(2);
		z_range--;
	}
	delay(500);
	setDir('z', POS);
	while (digitalRead(Z_MAX_PIN) == 1)
	{
		digitalWrite(Z_STEP_PIN,1);
		delay(4);
		digitalWrite(Z_STEP_PIN,0);
		delay(4);
		z_range++;
	}
	delay(500);
	z_range -= 2*SAFETY;

  x_pos = x_range + SAFETY;
  y_pos = y_range + SAFETY;
  z_pos = z_range + SAFETY;

  Serial.print("x_range = ");
  Serial.println(x_range);
  Serial.print("y_range = ");
  Serial.println(y_range);
  Serial.print("z_range = ");
  Serial.println(z_range);

  return 0;
}
*/
