void setupPins(void)
{
  // Set up pin modes
  pinMode(FAN_PIN , OUTPUT);
  pinMode(HEATER_0_PIN , OUTPUT);
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
  
  pinMode(Q_STEP_PIN  , OUTPUT);
  pinMode(Q_DIR_PIN    , OUTPUT);
  pinMode(Q_ENABLE_PIN    , OUTPUT);
  
  digitalWrite(X_ENABLE_PIN    , LOW);
  digitalWrite(Y_ENABLE_PIN    , LOW);
  digitalWrite(Z_ENABLE_PIN    , LOW);
  digitalWrite(E_ENABLE_PIN    , LOW);
  digitalWrite(Q_ENABLE_PIN    , LOW);

  // unused
  pinMode(START_PIN, INPUT_PULLUP);

  pinMode(LEFT,INPUT_PULLUP);
  pinMode(RIGHT,INPUT_PULLUP);
  pinMode(FORWARDS,INPUT_PULLUP);
  pinMode(BACKWARDS,INPUT_PULLUP);
  pinMode(SKY,INPUT_PULLUP);
  pinMode(FLOOR,INPUT_PULLUP);

  // interrupts
  //attachInterrupt(digitalPinToInterrupt(X_MIN_PIN), endstopInterrupt, CHANGE);
  //attachInterrupt(digitalPinToInterrupt(X_MAX_PIN), endstopInterrupt, CHANGE);
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

    // FIND MINIMUM OF Z-AXIS
  digitalWrite(Z_DIR_PIN, UP);
  while (digitalRead(Z_MAX_PIN) == 1)
  {
    digitalWrite(Z_STEP_PIN,1);
    delay(1);
    digitalWrite(Z_STEP_PIN,0);
    delay(1);
  }
  digitalWrite(Z_DIR_PIN, DOWN);
  for (i = 0; i < SAFETY; i++)
  {
    digitalWrite(Z_STEP_PIN,1);
    delay(1);
    digitalWrite(Z_STEP_PIN,0);
    delay(1);
  }

  // FIND MAXIMUM OF Z-AXIS
  digitalWrite(Z_DIR_PIN, DOWN);
  while (digitalRead(Z_MIN_PIN) == 1)
  {
    digitalWrite(Z_STEP_PIN,1);
    delay(1);
    digitalWrite(Z_STEP_PIN,0);
    delay(1);
    z_range++;
  }
  digitalWrite(Z_DIR_PIN, UP);
  for (i = 0; i < SAFETY; i++)
  {
    digitalWrite(Z_STEP_PIN,1);
    delay(1);
    digitalWrite(Z_STEP_PIN,0);
    delay(1);
    z_range--;
  }
  
  // FIND MINIMUM OF X-AXIS
  digitalWrite(X_DIR_PIN, DOWN);
  digitalWrite(E_DIR_PIN, UP);
  while (digitalRead(X_MIN_PIN) == 1)
  {
    digitalWrite(X_STEP_PIN,1);
    digitalWrite(E_STEP_PIN,1);
    delay(1);
    digitalWrite(X_STEP_PIN,0);
    digitalWrite(E_STEP_PIN,0);
    delay(1);
  }
  digitalWrite(X_DIR_PIN, UP);
  digitalWrite(E_DIR_PIN, DOWN);
  for (i = 0; i < SAFETY; i++)
  {
    digitalWrite(X_STEP_PIN,1);
    digitalWrite(E_STEP_PIN,1);
    delay(1);
    digitalWrite(X_STEP_PIN,0);
    digitalWrite(E_STEP_PIN,0);
    delay(1);
  }

  // FIND MAXIMUM OF X-AXIS
  digitalWrite(X_DIR_PIN, UP);
  digitalWrite(E_DIR_PIN, DOWN);
  while (digitalRead(X_MAX_PIN) == 1)
  {
    digitalWrite(X_STEP_PIN,1);
    digitalWrite(E_STEP_PIN,1);
    delay(1);
    digitalWrite(X_STEP_PIN,0);
    digitalWrite(E_STEP_PIN,0);
    delay(1);
    x_range++;
  }
  digitalWrite(X_DIR_PIN, DOWN);
  digitalWrite(E_DIR_PIN, UP);
  for (i = 0; i < SAFETY; i++)
  {
    digitalWrite(X_STEP_PIN,1);
    digitalWrite(E_STEP_PIN,1);
    delay(1);
    digitalWrite(X_STEP_PIN,0);
    digitalWrite(E_STEP_PIN,0);
    delay(1);
    x_range--;
  }
  
  // FIND MINIMUM OF Y-AXIS
  digitalWrite(Y_DIR_PIN, DOWN);
  while (digitalRead(Y_MIN_PIN) == 1)
  {
    digitalWrite(Y_STEP_PIN,1);
    delay(1);
    digitalWrite(Y_STEP_PIN,0);
    delay(1);
  }
  digitalWrite(Y_DIR_PIN, UP);
  for (i = 0; i < SAFETY; i++)
  {
    digitalWrite(Y_STEP_PIN,1);
    delay(1);
    digitalWrite(Y_STEP_PIN,0);
    delay(1);
  }
  
  // FIND MAXIMUM OF Y-AXIS
  digitalWrite(Y_DIR_PIN, UP);
  while (digitalRead(Y_MAX_PIN) == 1)
  {
    digitalWrite(Y_STEP_PIN,1);
    delay(1);
    digitalWrite(Y_STEP_PIN,0);
    delay(1);
    y_range++;
  }
  digitalWrite(Y_DIR_PIN, DOWN);
  for (i = 0; i < SAFETY; i++)
  {
    digitalWrite(Y_STEP_PIN,1);
    delay(1);
    digitalWrite(Y_STEP_PIN,0);
    delay(1);
    y_range--;
  }

  x_pos = x_range;
  y_pos = y_range;
  z_pos = z_range;
}
