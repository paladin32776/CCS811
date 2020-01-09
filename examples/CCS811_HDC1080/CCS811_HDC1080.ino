#include "CCS811.h"
#include "HDC1080.h"

CCS811 ccs;
HDC1080 hdc;

void setup()
{
  Serial.begin(115200);
  delay(50);
}

void loop()
{
  float T, RH;
  hdc.read(&T, &RH);
  ccs.set_env_data(T, RH);
  unsigned int CO2, TVOC;
  ccs.read(&CO2, &TVOC);
  Serial.printf("T = %1.1f  RH=%-1.1f  CO2 = %d  TVOC = %d\n", T, RH, CO2, TVOC);
  delay(500);
}
