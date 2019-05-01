#include "pins.h"
#include "definitions.h"
#include "globals.h"

#include "box_logic.h"
#include "init.h"
#include "move.h"

// Cases
#include "normal_run.h" /* 0*/
#include "box_logic_test.h" /* 1 */
#include "loss_test.h" /* 2 */
#include "print_pos.h" /* 3 */
// 4 is print_pos without calibration
#define CASE_NUM 2 /* Cases numbered as above starting at 0 */



// global variables for size of each dimension
volatile int x_range = 0;
volatile int y_range = 0;
volatile int z_range = 0;

// global variables for current position
volatile int x_pos = 0;
volatile int y_pos = 0;
volatile int z_pos = 0;

void setup() {

  Serial.begin(9600);

  Serial.println("Beginning Startup...");

  setupPins();

  if (CASE_NUM == 4 || CASE_NUM == 2)
  {
    return;
  }

  if (CASE_NUM == 0)
  {
	  calibrate();
	  Serial.println("calibrated");
  }
  else
  {
	  zero();
	  Serial.println("zeroed");
  }

  if (go(0,0,z_range) != 0)
  {
    while (1);  // fail if the go command messes up
  }
  Serial.println("moved to (0,0,z_range)");
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
    case 4:
      print_pos();
    default:
      while(1);
      break;
  }
}
