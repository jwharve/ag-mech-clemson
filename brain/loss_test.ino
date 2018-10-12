void loss_test(void)
{
  Serial.println("loss_test");
  testX();
  testY();
  testZ();
  testX();
  testY();
  testZ();
  while(1);
}

void testX()
{
  int i;
  char dir = 1;
  int temp;

  int x_axis_size[NUM_TESTS];
  for (i = 0; i < NUM_TESTS; i++) {x_axis_size[i] = 0;}


  setDir('x',NEG);
  while (digitalRead(X_MIN_PIN) == 1)
  {
    digitalWrite(X_STEP_PIN,1);
    digitalWrite(E_STEP_PIN,1);
    delay(1);
    digitalWrite(X_STEP_PIN,0);
    digitalWrite(E_STEP_PIN,0);
    delay(1);
  }
  
  for (i=0; i < NUM_TESTS; i++)
  {
    temp = 0;
    
    if (dir == POS)
    {
      setDir('x',POS);
      dir = NEG;
      while (digitalRead(X_MAX_PIN) == 1)
      {
        digitalWrite(X_STEP_PIN,1);
        digitalWrite(E_STEP_PIN,1);
        delay(1);
        digitalWrite(X_STEP_PIN,0);
        digitalWrite(E_STEP_PIN,0);
        delay(1);
        temp++;
      }
    }
    else
    {
      setDir('x',NEG);
      dir = POS;
      while (digitalRead(X_MIN_PIN) == 1)
      {
        digitalWrite(X_STEP_PIN,1);
        digitalWrite(E_STEP_PIN,1);
        delay(1);
        digitalWrite(X_STEP_PIN,0);
        digitalWrite(E_STEP_PIN,0);
        delay(1);
        temp++;
      }
    }
    
    x_axis_size[i] = temp;
  }

  Serial.println("X AXIS RESULTS:");
  for (i = 0; i < NUM_TESTS; i++)
  {
    Serial.println(x_axis_size[i]);
  }
  Serial.println();
}

void testY()
{
  int i;
  char dir = 1;
  int temp;

  int y_axis_size[NUM_TESTS];
  for (i = 0; i < NUM_TESTS; i++) {y_axis_size[i] = 0;}


  setDir('y',NEG);
  while (digitalRead(Y_MIN_PIN) == 1)
  {
    digitalWrite(Y_STEP_PIN,1);
    delay(1);
    digitalWrite(Y_STEP_PIN,0);
    delay(1);
  }
  
  for (i=0; i < NUM_TESTS; i++)
  {
    temp = 0;
    
    if (dir == POS)
    {
      setDir('y',POS);
      dir = NEG;
      while (digitalRead(Y_MAX_PIN) == 1)
      {
        digitalWrite(Y_STEP_PIN,1);
        delay(1);
        digitalWrite(Y_STEP_PIN,0);
        delay(1);
        temp++;
      }
    }
    else
    {
      setDir('y',NEG);
      dir = POS;
      while (digitalRead(Y_MIN_PIN) == 1)
      {
        digitalWrite(Y_STEP_PIN,1);
        delay(1);
        digitalWrite(Y_STEP_PIN,0);
        delay(1);
        temp++;
      }
    }
    
    y_axis_size[i] = temp;
  }

  Serial.println("Y AXIS RESULTS:");
  for (i = 0; i < NUM_TESTS; i++)
  {
    Serial.println(y_axis_size[i]);
  }
  Serial.println();
}

void testZ()
{
  int i;
  char dir = 1;
  int temp;

  int z_axis_size[NUM_TESTS];
  for (i = 0; i < NUM_TESTS; i++) {z_axis_size[i] = 0;}


  setDir('z',NEG);
  while (digitalRead(Z_MIN_PIN) == 1)
  {
    digitalWrite(Z_STEP_PIN,1);
    delay(1);
    digitalWrite(Z_STEP_PIN,0);
    delay(1);
  }
  
  for (i=0; i < NUM_TESTS; i++)
  {
    temp = 0;
    
    if (dir == POS)
    {
      setDir('z',POS);
      dir = NEG;
      while (digitalRead(Z_MAX_PIN) == 1)
      {
        digitalWrite(Z_STEP_PIN,1);
        delay(1);
        digitalWrite(Z_STEP_PIN,0);
        delay(1);
        temp++;
      }
    }
    else
    {
      setDir('z',NEG);
      dir = POS;
      while (digitalRead(Z_MIN_PIN) == 1)
      {
        digitalWrite(Z_STEP_PIN,1);
        delay(1);
        digitalWrite(Z_STEP_PIN,0);
        delay(1);
        temp++;
      }
    }
    
    z_axis_size[i] = temp;
  }

  Serial.println("Z AXIS RESULTS:");
  for (i = 0; i < NUM_TESTS; i++)
  {
    Serial.println(z_axis_size[i]);
  }
  Serial.println();
}
