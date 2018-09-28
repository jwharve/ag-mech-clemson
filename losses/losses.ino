#include "config.h"
#include "pins.h"

#define DEBUG 0 /* 0 disables debug printing */

#define NUM_TESTS 20

// global variables for size of each dimension
volatile int x_range = 0;
volatile int y_range = 0;
volatile int z_range = 0;

// global variables for current position
volatile int x_pos = 0;
volatile int y_pos = 0;
volatile int z_pos = 0;

#define DOWN LOW
#define UP HIGH

void setup() {

  setupPins();

  Serial.begin(9600);
}

void loop () {

  testX();
  testY();
  
  while (1);
}

void testX()
{
  int i;
  char dir = 1;
  int temp;

  int x_axis_size[NUM_TESTS];
  for (i = 0; i < NUM_TESTS; i++) {x_axis_size[i] = 0;}


  digitalWrite(X_DIR_PIN, DOWN);
  digitalWrite(E_DIR_PIN, UP);
  while (digitalRead(X_MAX_PIN) == 1 && digitalRead(X_MIN_PIN) == 1)
  {
    digitalWrite(X_STEP_PIN,1);
    digitalWrite(E_STEP_PIN,1);
    delay(2);
    digitalWrite(X_STEP_PIN,0);
    digitalWrite(E_STEP_PIN,0);
  }
  dir = 1;
  
  for (i=0; i < NUM_TESTS; i++)
  {
    temp = 0;
    
    if (dir == 1)
    {
      digitalWrite(X_DIR_PIN, UP);
      digitalWrite(E_DIR_PIN, DOWN);
      dir = 0;
      while (digitalRead(X_MAX_PIN) == 1)
      {
        digitalWrite(X_STEP_PIN,1);
        digitalWrite(E_STEP_PIN,1);
        delay(2);
        digitalWrite(X_STEP_PIN,0);
        digitalWrite(E_STEP_PIN,0);
        temp++;
      }
    }
    else
    {
      digitalWrite(X_DIR_PIN,DOWN);
      digitalWrite(E_DIR_PIN,UP);
      dir = 1;
      while (digitalRead(X_MIN_PIN) == 1)
      {
        digitalWrite(X_STEP_PIN,1);
        digitalWrite(E_STEP_PIN,1);
        delay(2);
        digitalWrite(X_STEP_PIN,0);
        digitalWrite(E_STEP_PIN,0);
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

  digitalWrite(Y_DIR_PIN, DOWN);
  while (digitalRead(Y_MAX_PIN) == 1 && digitalRead(Y_MIN_PIN) == 1)
  {
    digitalWrite(Y_STEP_PIN,1);
    delay(2);
    digitalWrite(Y_STEP_PIN,0);
  }
  dir = 1;
  
  for (i=0; i < NUM_TESTS; i++)
  {
    temp = 0;
    
    if (dir == 1)
    {
      digitalWrite(Y_DIR_PIN, UP);
      dir = 0;
      while (digitalRead(Y_MAX_PIN) == 1)
      {
        digitalWrite(Y_STEP_PIN,1);
        delay(2);
        digitalWrite(Y_STEP_PIN,0);
        temp++;
      }
    }
    else
    {
      digitalWrite(Y_DIR_PIN,DOWN);
      dir = 1;
      while (digitalRead(Y_MIN_PIN) == 1)
      {
        digitalWrite(Y_STEP_PIN,1);
        delay(2);
        digitalWrite(Y_STEP_PIN,0);
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

