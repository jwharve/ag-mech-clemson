#include "pins.h"

void setup() {
  // put your setup code here, to run once:
  pinMode(Z_MIN_PIN,INPUT);
  pinMode(Z_MAX_PIN,INPUT);
  pinMode(Y_MIN_PIN,INPUT);
  pinMode(Y_MAX_PIN,INPUT);
  pinMode(X_MAX_PIN,INPUT);
  pinMode(X_MIN_PIN,INPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  Serial.print("Z_MIN_PIN = ");
  Serial.println(digitalRead(Z_MIN_PIN));
  Serial.print("Z_MAX_PIN = ");
  Serial.println(digitalRead(Z_MAX_PIN));
  Serial.print("Y_MIN_PIN = ");
  Serial.println(digitalRead(Y_MIN_PIN));
  Serial.print("Y_MAX_PIN = ");
  Serial.println(digitalRead(Y_MAX_PIN));
  Serial.print("X_MIN_PIN = ");
  Serial.println(digitalRead(X_MIN_PIN));
  Serial.print("X_MAX_PIN = ");
  Serial.println(digitalRead(X_MAX_PIN));
}
