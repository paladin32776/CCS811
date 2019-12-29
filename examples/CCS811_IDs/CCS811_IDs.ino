#include "HDC1080.h"

HDC1080 hdc;

void setup()
{
  Serial.begin(9600);
  delay(10);
  Serial.printf("MfgID = %04X  DevID = %04X  ", hdc.get_mfg_id(), hdc.get_device_id());
  unsigned int serial_id[3];
  hdc.get_serial_id(serial_id);
  Serial.printf("Ser = %04X %04X %04X\n", serial_id[0], serial_id[1], serial_id[2]);
}

void loop()
{
  float T,RH;
  hdc.read(&T, &RH);
  Serial.printf("T = %f  RH = %f\n", T, RH);
  delay(500);
}
