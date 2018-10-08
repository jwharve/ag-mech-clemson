#include "pins.h"
#include "config.h"

#include "box_logic.h"
#include "init.h"
#include "move.h"

#define DEBUG 0 /* 0 disables debug printing */

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

  if (go(0,0,z_range) != 0)
  {
    while (1);  // fail if the go command messes up
  }
  Serial.println("moved to (0,0,0)");  
  
}

void loop () {
  /* UNUSED START PIN
  while(digitalRead(START_PIN) != 0);
  Serial.println("go");
  */
  unsigned long start = millis();

  Serial.println("Starting the stuff");
  while(millis() - start < 10e3)
  {
  }
  Serial.println("hope it's right");
  Serial.print("X = ");Serial.println(x_pos);
  Serial.print("Y = ");Serial.println(y_pos);
  Box one(1311-132,255-132,13,11,132,313);

  one.goToUnit(3,3);
  delay(5000);
  one.goToUnit(10,10);
  delay(5000);
  one.goToUnit(0,0);
  while (1);
}
/*
first corner
X = 200
Y = 450

acroos corner
X = 200
Y = 3214

diagonal corner
X = 2565
Y = 3214
*/
