#include "box_logic_test.h"

void box_logic_test(void)
{
  Serial.println("box_logic_test");

//  unsigned long start = millis();

  Box one(2771-0,2374-0,14,12,0,0);

	Serial.println("Going to (3,3)");

  one.goToUnit(3,3);
  pump(ON);
  delay(750);
  pump(OFF);

	Serial.println("Going to (10,10)");

  one.goToUnit(10,10);
  pump(ON);
  delay(750);
  pump(OFF);
  one.goToUnit(0,0);

  one.seed(0,0,2,4);
  while (1);
}
