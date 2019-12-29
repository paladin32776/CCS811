#include "HDC1080.h"
#define PRINTBIN(Num) for (uint32_t t = (1UL<< (sizeof(Num)*8)-1); t; t >>= 1) Serial.write(Num  & t ? '1' : '0'); // Prints a binary number with leading zeros (Automatic Handling)

HDC1080::HDC1080()
{
  Wire.begin(14,2);
  addr = 64;
  delay(20);
  write_word(HDC_CONFIG, 0b0001000000000000);
}

unsigned char HDC1080::read_byte(unsigned char regbyte)
{
  Wire.beginTransmission(addr);
  Wire.write(byte(regbyte));
  Wire.endTransmission(false);
  Wire.requestFrom(addr, (byte)1);
  unsigned char databyte = Wire.read();
  return databyte;
}

unsigned int HDC1080::read_word(unsigned char regbyte)
{
  Wire.beginTransmission(addr);
  Wire.write(byte(regbyte));
  Wire.endTransmission(false);
  Wire.requestFrom(addr, (byte)2);
  unsigned int dataword = 0;
  while (Wire.available())
    dataword = (dataword<<8)+Wire.read();
  return dataword;
}

void HDC1080::write_regbyte(unsigned char regbyte)
{
  Wire.beginTransmission(addr);         // transmit to device #addr
  Wire.write(byte(regbyte));            // sends instruction byte
  Wire.endTransmission();               // stop transmitting
}

void HDC1080::write_byte(unsigned char regbyte, unsigned char databyte)
{
  Wire.beginTransmission(addr);         // transmit to device #addr
  Wire.write(byte(regbyte));            // sends instruction byte
  Wire.write(byte(databyte));           // sends value byte
  Wire.endTransmission();               // stop transmitting
}

void HDC1080::write_word(unsigned char regbyte, unsigned int dataword)
{
  Wire.beginTransmission(addr);         // transmit to device #addr
  Wire.write(byte(regbyte));            // sends instruction byte
  Wire.write(byte(dataword>>8));        // sends upper byte
  Wire.write(byte(dataword & 0xFF));    // sends lower byte
  Wire.endTransmission();               // stop transmitting
}

void HDC1080::read(float* temperature, float* humidity)
{
  write_regbyte(HDC_TEMPERATURE);
  delay(15);
  Wire.requestFrom(addr, (byte)4);
  unsigned int TEMPERATURE = (Wire.read()<<8)+Wire.read();
  unsigned int HUMIDITY = (Wire.read()<<8)+Wire.read();
  *temperature = ((float)TEMPERATURE) / 65536.0 * 165.0 - 40.0;
  *humidity = ((float)HUMIDITY) / 65536.0 * 100.0;
}

void HDC1080::get_serial_id(unsigned int* serial_id)
{
  serial_id[0] = read_word(HDC_SERIALID1);
  serial_id[1] = read_word(HDC_SERIALID2);
  serial_id[2] = read_word(HDC_SERIALID3);
}

unsigned int HDC1080::get_mfg_id()
{
  return read_word(HDC_MFGID);
}

unsigned int HDC1080::get_device_id()
{
  return read_word(HDC_DEVICEID);
}
