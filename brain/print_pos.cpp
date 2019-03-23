#include "print_pos.h"

void print_pos(void)
{
  Serial.println("print_pos");

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
