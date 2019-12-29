#include "HDC1080.h"

HDC1080 hdc;

void setup()
{
  Serial.begin(9600);
}

void loop()
{
  float T,RH;
  hdc.read(&T, &RH);
  Serial.printf("T = %f  RH = %f\n", T, RH);
  delay(500);
}
