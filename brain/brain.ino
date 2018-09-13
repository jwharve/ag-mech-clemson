#include "config.h"
#include "pins.h"

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

  Serial.begin(115200);

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
  /* UNUSED START PIN
  while(digitalRead(START_PIN) != 0);
  Serial.println("go");
  */
  int strafe /* X */, dir /* Y */, vert /* Z */;
  
  // LEFT AND RIGHT
  if (digitalRead(RIGHT) == 0)
  {
    strafe = 1;
  }
  else if (digitalRead(LEFT) == 0)
  {
    strafe = -1;
  }
  else
  {
    strafe = 0;
  }

  // FORWARDS AND BACKWARDS
  if (digitalRead(FORWARDS) == 0)
  {
    dir = 1;
  }
  else if (digitalRead(BACKWARDS) == 0)
  {
    dir = -1;
  }
  else
  {
    dir = 0;
  }

  // UP AND DOWN
  if (digitalRead(SKY) == 0)
  {
    vert = 1;
  }
  else if (digitalRead(FLOOR) == 0)
  {
    vert = -1;
  }
  else
  {
    vert = 0;
  }

  if (DEBUG)
  {
    Serial.print("Strafe = ");
    Serial.println(strafe);
    Serial.print("Dir= ");
    Serial.println(dir);
    Serial.print("Vert = ");
    Serial.println(vert);
    delay(1000);
  }

  stepX(strafe);
  stepY(dir);
  stepZ(vert);
  delay(1);

}
