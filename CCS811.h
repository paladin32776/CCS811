#include "Arduino.h"
#include <Wire.h>

#define HDC_TEMPERATURE 0x00
#define HDC_HUMIDITY 0x01
#define HDC_CONFIG 0x02
#define HDC_SERIALID1 0xFB
#define HDC_SERIALID2 0xFC
#define HDC_SERIALID3 0xFD
#define HDC_MFGID 0xFE
#define HDC_DEVICEID 0xFF

#define HDC_CFG_RST 15
#define HDC_CFG_HEAT 13
#define HDC_CFG_MODE 12
#define HDC_CFG_BTST 11
#define HDC_CFG_TRES 10
#define HDC_CFG_HRES_MSB 9
#define HDC_CFG_HRES_LSB 8

class HDC1080
{
  private:
    unsigned char addr;
    unsigned char read_byte(unsigned char regbyte);
    unsigned int read_word(unsigned char regbyte);
    void write_regbyte(unsigned char regbyte);
    void write_byte(unsigned char regbyte, unsigned char databyte);
    void write_word(unsigned char regbyte, unsigned int dataword);
  public:
    HDC1080();
    void get_serial_id(unsigned int* serial_id);
    unsigned int get_mfg_id();
    unsigned int get_device_id();
    void read(float* temperature, float* humidity);
};
