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
  unsigned int CO2, TVOC;
  ccs.read(&CO2, &TVOC);
  Serial.printf("CO2 = %d  TVOC = %d\n", CO2, TVOC);
  delay(500);
}
