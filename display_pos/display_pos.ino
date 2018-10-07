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
    
    if (millis() - last > 1e3)
    {
      last = millis();
      Serial.print("X = ");Serial.println(x_pos);
      Serial.print("Y = ");Serial.println(y_pos);
      Serial.print("Z = ");Serial.println(z_pos);
      Serial.println();
    }
  }
}

/*
 * 
first corner
X = 238
Y = 428
Z = 3065

acroos corner
X = 190
Y = 3222
Z = 3065

diagonal corner
X = 190
Y = 3222
Z = 3065



 * */
 */

