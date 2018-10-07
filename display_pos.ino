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
  
  if (calibrate() != 0)
  {
    while (1);  // fail if the calibrate messes up
  }
  Serial.println("calibrated");

  if (go(0,0,0) != 0)
  {
    while (1);  // fail if the go command messes up
  }
  Serial.println("moved to (0,0,0)");
}

void loop () {

  unsigned long last = millis();
  
  while (1)
  {
    buttonMove();
    
    if (last -  millis() > 1e3)
    {
      last = millis();
      Serial.print("X = ");Serial.println(x_pos);
      Serial.print("Y = ");Serial.println(y_pos);
      Serial.print("Z = ");Serial.println(z_pos);
      Serial.println();
    }
  }
}
