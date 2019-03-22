#include "print_endstops.h"

void print_endstops(void)
{
  Serial.println("box_logic_test");
  
  while (1)
  {
    Serial.print("X_MIN_PIN - ");
    Serial.println(digitalRead(X_MIN_PIN));
    Serial.print("X_MAX_PIN - ");
    Serial.println(digitalRead(X_MAX_PIN));
    Serial.print("Y_MIN_PIN - ");
    Serial.println(digitalRead(Y_MIN_PIN));
    Serial.print("Y_MAX_PIN - ");
    Serial.println(digitalRead(Y_MAX_PIN));
    Serial.print("Z_MIN_PIN - ");
    Serial.println(digitalRead(Z_MIN_PIN));
    Serial.print("Z_MAX_PIN - ");
    Serial.println(digitalRead(Z_MAX_PIN));
    Serial.println("----------------------");
    delay(1000);
  }
}
/*
First Corner - 0 411
2 - 2429 411
3 - 2429 3001
*/
