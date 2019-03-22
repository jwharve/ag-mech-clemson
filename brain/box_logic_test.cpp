#include "box_logic_test.h"

void box_logic_test(void)
{
  Serial.println("box_logic_test");

  unsigned long start = millis();

  Box one(2429-0,2650,12,13,0,0);

  one.goToUnit(3,3);
  delay(5000);
  one.goToUnit(10,10);
  delay(5000);
  one.goToUnit(0,0);

  one.seed(0,0,2,4);
  while (1);
}
/*
First Corner - 0 411
2 - 2429 411
3 - 2429 3001
*/
