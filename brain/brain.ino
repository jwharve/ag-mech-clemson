#include "pins.h"
#include "definitions.h"

#include "box_logic.h"
#include "init.h"
#include "move.h"

// Cases
#include "normal_run.h"
#include "box_logic_test.h"
#include "loss_test.h"
#include "print_pos.h"
#define CASE_NUM 0 /* Cases numbered as above starting at 0 */

#define DEBUG 0 /* 0 disables debug printing */



// global variables for size of each dimension
volatile int x_range = 0;
volatile int y_range = 0;
volatile int z_range = 0;

// global variables for current position
volatile int x_pos = 0;
volatile int y_pos = 0;
volatile int z_pos = 0;

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

  switch (CASE_NUM)
  {
    case 0:
      normal_run();
      break;
    case 1:
      box_logic_test();
      break;
    case 2:
      // need to disable interrupts
      loss_test();
      break;
    case 3:
      print_pos();
    default:
      while(1);
      break;
  }
}
