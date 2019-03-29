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

  digitalWrite(X_ENABLE_PIN    , LOW);
  digitalWrite(Y_ENABLE_PIN    , LOW);
  digitalWrite(Z_ENABLE_PIN    , LOW);
  digitalWrite(E_ENABLE_PIN    , LOW);

  // Controller Setup
  pinMode(X_P,INPUT_PULLUP);
  pinMode(X_N,INPUT_PULLUP);
  pinMode(Y_P,INPUT_PULLUP);
  pinMode(Y_N,INPUT_PULLUP);
  pinMode(Z_P,INPUT_PULLUP);
  pinMode(Z_N,INPUT_PULLUP);
  pinMode(P_1,INPUT_PULLUP);
  pinMode(P_2,INPUT_PULLUP);


  // interrupts
  //attachInterrupt(digitalPinToInterrupt(X_MIN_PIN), endstopInterrupt, CHANGE);  //attachInterrupt(digitalPinToInterrupt(X_MAX_PIN), endstopInterrupt, CHANGE);
  //attachInterrupt(digitalPinToInterrupt(Y_MIN_PIN), endstopInterrupt, CHANGE);
  //attachInterrupt(digitalPinToInterrupt(Y_MAX_PIN), endstopInterrupt, CHANGE);
  //attachInterrupt(digitalPinToInterrupt(Z_MIN_PIN), endstopInterrupt, CHANGE);
  //attachInterrupt(digitalPinToInterrupt(Z_MAX_PIN), endstopInterrupt, CHANGE);
}

/*
This function calibrates the endpoints of the machine
It provides a safety margin of SAFETY steps
Goes from x-min to x-max, y-min to y-max, then z-min to z-max.
*/
int calibrate()
{
  int i;
  float del[NUM_RAMP];
  float delS[SAFETY];
  
  
  // Initialize del
  del[0] = START_DELAY * 1000;
  for (i = 1; i < NUM_RAMP; i++)
  {
	del[i] = del[i-1]/(float)ACCEL;
  }
  // Initialize delS
  delS[0] = START_DELAY * 1000;
  for (i = 1; i < SAFETY/2 && i < NUM_RAMP; i++) 
  {
	delS[i] = delS[i-1]/(float)ACCEL;
  }
  for (; i < SAFETY; i++) // trying no ramp down
  {
  	delS[i] = 1000;
  }
  for (; i < SAFETY; i++)
  {
  	delS[i] = delS[i-1]*ACCEL;
  }
  
		// FIND MAXIMUM OF Z-AXIS
	setDir('z', POS);
	i = 0;
	while (digitalRead(Z_MAX_PIN) == 1)
	{
		if (i < NUM_RAMP)
		{
			digitalWrite(Z_STEP_PIN,1);
			delayMicroseconds(static_cast<int>(del[i]));
			digitalWrite(Z_STEP_PIN,1);
			delayMicroseconds(static_cast<int>(del[i]));
			i++;
		}
		digitalWrite(Z_STEP_PIN,1);
		delay(1);
		digitalWrite(Z_STEP_PIN,0);
		delay(1);
	}
	
	
	// FIND MINIMUM OF X-AXIS
	setDir('x', NEG);
	i = 0;
	while (digitalRead(X_MIN_PIN) == 1)
	{
		if (i < NUM_RAMP)
		{
			digitalWrite(X_STEP_PIN,1);
			delayMicroseconds(static_cast<int>(del[i]));
			digitalWrite(X_STEP_PIN,1);
			delayMicroseconds(static_cast<int>(del[i]));
			i++;
		}
		digitalWrite(X_STEP_PIN,1);
		delay(1);
		digitalWrite(X_STEP_PIN,0);
		delay(1);
	}
	// GO SLOW
	setDir('x', POS);
	while (digitalRead(X_MIN_PIN) == 0)
	{
		}
		digitalWrite(X_STEP_PIN,1);
		delay(2);
		digitalWrite(X_STEP_PIN,0);
		delay(2);
	}
	setDir('x', POS);
	while (digitalRead(X_MIN_PIN) == 1)
	{
		}
		digitalWrite(X_STEP_PIN,1);
		delay(2);
		digitalWrite(X_STEP_PIN,0);
		delay(2);
	}
	
	// FIND MAXIMUM OF X-AXIS
	setDir('x', POS);
	i = 0;
	while (digitalRead(X_MAX_PIN) == 1)
	{
		if (i < NUM_RAMP)
		{
			digitalWrite(X_STEP_PIN,1);
			delayMicroseconds(static_cast<int>(del[i]));
			digitalWrite(X_STEP_PIN,1);
			delayMicroseconds(static_cast<int>(del[i]));
			i++;
			x_range++;
		}
		digitalWrite(X_STEP_PIN,1);
		delay(1);
		digitalWrite(X_STEP_PIN,0);
		delay(1);
			x_range++;
	}
	// GO SLOW
	setDir('x', NEG);
	while (digitalRead(X_MAX_PIN) == 0)
	{
		}
		digitalWrite(X_STEP_PIN,1);
		delay(2);
		digitalWrite(X_STEP_PIN,0);
		delay(2);
			x_range--;
	}
	setDir('x', NEG);
	while (digitalRead(X_MAX_PIN) == 1)
	{
		}
		digitalWrite(X_STEP_PIN,1);
		delay(2);
		digitalWrite(X_STEP_PIN,0);
		delay(2);
			x_range++;
	}
	x_range -= 2*SAFETY;
	
	
	// FIND MINIMUM OF Y-AXIS
	setDir('y', NEG);
	i = 0;
	while (digitalRead(Y_MIN_PIN) == 1)
	{
		if (i < NUM_RAMP)
		{
			digitalWrite(Y_STEP_PIN,1);
			digitalWrite(E_STEP_PIN,1);
			delayMicroseconds(static_cast<int>(del[i]));
			digitalWrite(Y_STEP_PIN,1);
			digitalWrite(E_STEP_PIN,1);
			delayMicroseconds(static_cast<int>(del[i]));
			i++;
		}
		digitalWrite(Y_STEP_PIN,1);
		digitalWrite(E_STEP_PIN,1);
		delay(1);
		digitalWrite(Y_STEP_PIN,0);
		digitalWrite(E_STEP_PIN,0);
		delay(1);
	}
	// GO SLOW
	setDir('y', POS);
	while (digitalRead(Y_MIN_PIN) == 0)
	{
		}
		digitalWrite(Y_STEP_PIN,1);
		digitalWrite(E_STEP_PIN,1);
		delay(2);
		digitalWrite(Y_STEP_PIN,0);
		digitalWrite(E_STEP_PIN,0);
		delay(2);
	}
	setDir('y', POS);
	while (digitalRead(Y_MIN_PIN) == 1)
	{
		}
		digitalWrite(Y_STEP_PIN,1);
		digitalWrite(E_STEP_PIN,1);
		delay(2);
		digitalWrite(Y_STEP_PIN,0);
		digitalWrite(E_STEP_PIN,0);
		delay(2);
	}
	
	// FIND MAXIMUM OF Y-AXIS
	setDir('y', POS);
	i = 0;
	while (digitalRead(Y_MAX_PIN) == 1)
	{
		if (i < NUM_RAMP)
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
		digitalWrite(Y_STEP_PIN,1);
		digitalWrite(E_STEP_PIN,1);
		delay(1);
		digitalWrite(Y_STEP_PIN,0);
		digitalWrite(E_STEP_PIN,0);
		delay(1);
			y_range++;
	}
	// GO SLOW
	setDir('y', NEG);
	while (digitalRead(Y_MAX_PIN) == 0)
	{
		}
		digitalWrite(Y_STEP_PIN,1);
		digitalWrite(E_STEP_PIN,1);
		delay(2);
		digitalWrite(Y_STEP_PIN,0);
		digitalWrite(E_STEP_PIN,0);
		delay(2);
			y_range--;
	}
	setDir('y', NEG);
	while (digitalRead(Y_MAX_PIN) == 1)
	{
		}
		digitalWrite(Y_STEP_PIN,1);
		digitalWrite(E_STEP_PIN,1);
		delay(2);
		digitalWrite(Y_STEP_PIN,0);
		digitalWrite(E_STEP_PIN,0);
		delay(2);
			y_range++;
	}
	y_range -= 2*SAFETY;
	
	
	// FIND MINIMUM OF Z-AXIS
	setDir('z', NEG);
	i = 0;
	while (digitalRead(Z_MIN_PIN) == 1)
	{
		if (i < NUM_RAMP)
		{
			digitalWrite(Z_STEP_PIN,1);
			delayMicroseconds(static_cast<int>(del[i]));
			digitalWrite(Z_STEP_PIN,1);
			delayMicroseconds(static_cast<int>(del[i]));
			i++;
		}
		digitalWrite(Z_STEP_PIN,1);
		delay(1);
		digitalWrite(Z_STEP_PIN,0);
		delay(1);
	}
	// GO SLOW
	setDir('z', POS);
	while (digitalRead(Z_MIN_PIN) == 0)
	{
		}
		digitalWrite(Z_STEP_PIN,1);
		delay(2);
		digitalWrite(Z_STEP_PIN,0);
		delay(2);
	}
	setDir('z', POS);
	while (digitalRead(Z_MIN_PIN) == 1)
	{
		}
		digitalWrite(Z_STEP_PIN,1);
		delay(2);
		digitalWrite(Z_STEP_PIN,0);
		delay(2);
	}
	
	// FIND MAXIMUM OF Z-AXIS
	setDir('z', POS);
	i = 0;
	while (digitalRead(Z_MAX_PIN) == 1)
	{
		if (i < NUM_RAMP)
		{
			digitalWrite(Z_STEP_PIN,1);
			delayMicroseconds(static_cast<int>(del[i]));
			digitalWrite(Z_STEP_PIN,1);
			delayMicroseconds(static_cast<int>(del[i]));
			i++;
			z_range++;
		}
		digitalWrite(Z_STEP_PIN,1);
		delay(1);
		digitalWrite(Z_STEP_PIN,0);
		delay(1);
			z_range++;
	}
	// GO SLOW
	setDir('z', NEG);
	while (digitalRead(Z_MAX_PIN) == 0)
	{
		}
		digitalWrite(Z_STEP_PIN,1);
		delay(2);
		digitalWrite(Z_STEP_PIN,0);
		delay(2);
			z_range--;
	}
	setDir('z', NEG);
	while (digitalRead(Z_MAX_PIN) == 1)
	{
		}
		digitalWrite(Z_STEP_PIN,1);
		delay(2);
		digitalWrite(Z_STEP_PIN,0);
		delay(2);
			z_range++;
	}
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

