#include "CCS811.h"
#define PRINTBIN(Num) for (uint32_t t = (1UL<< (sizeof(Num)*8)-1); t; t >>= 1) Serial.write(Num  & t ? '1' : '0'); // Prints a binary number with leading zeros (Automatic Handling)

CCS811::CCS811(): I2C_COMM(CCS_DEFAULT_ADDRESS)
{
  init();
}

CCS811::CCS811(unsigned char _addr): I2C_COMM(_addr)
{
  init();
}

CCS811::CCS811(unsigned char SDApin, unsigned char SCLpin): I2C_COMM(CCS_DEFAULT_ADDRESS, SDApin, SCLpin)
{
  init();
}

CCS811::CCS811(unsigned char _addr, unsigned char SDApin, unsigned char SCLpin): I2C_COMM(_addr, SDApin, SCLpin)
{
  init();
}

void CCS811::init()
{
  unsigned char status = get_status();
  if ((status & CCS_APP_VALID_MASK) && !(status & CCS_FW_MODE_MASK))
  {
    write_regbyte(CSS_APP_START);
    status = get_status();
  }
  if (status & CCS_FW_MODE_MASK)
  {
    app_mode = true;
    set_drive_mode(1);
    if (get_drive_mode()==1)
      running = true;
  }
}

bool CCS811::data_ready()
{
  return (get_status() & CCS_DATA_READY_MASK)>0;
}

bool CCS811::iserror()
{
  return (get_status() & CCS_ERROR_MASK)>0;
}

unsigned char CCS811::get_status()
{
  return read_byte(CCS_STATUS);
}

void CCS811::set_drive_mode(unsigned int drive_mode)
{
  meas_mode = (meas_mode & ~CCS_DRIVE_MODE_MASK) | ((drive_mode<<4) & CCS_DRIVE_MODE_MASK);
  write_byte(CCS_MEAS_MODE, meas_mode);
}

unsigned int CCS811::get_drive_mode()
{
  meas_mode = read_byte(CCS_MEAS_MODE);
  return (meas_mode & CCS_DRIVE_MODE_MASK)>>4;
}

unsigned char CCS811::get_hw_id()
{
  return read_byte(CCS_HW_ID);
}

unsigned char CCS811::get_hw_version()
{
  return read_byte(CCS_HW_VERSION);
}

unsigned int CCS811::get_fw_boot_version()
{
  return read_word(CCS_FW_BOOT_VERSION);
}

unsigned char CCS811::get_error_id()
{
  return read_byte(CCS_ERROR_ID);
}

void CCS811::read(unsigned int* _CO2, unsigned int* _TVOC)
{
  if (app_mode && running && data_ready())
  {
    unsigned char data[4];
    read_multi_bytes(CCS_ALG_RESULT_DATA, 4, data);
    CO2 = (data[0]<<8) + data[1];
    TVOC = (data[2]<<8) + data[3];
  }
  *_CO2 = CO2;
  *_TVOC = TVOC;
}

void CCS811::set_env_data(float T, float RH)
{
  unsigned char bytes[4];
  unsigned int T_int = (unsigned int)((T+25)*512);
  // Serial.printf("T = %f  T_int = %d (0x%04X)\n", T, T_int , T_int );
  unsigned int RH_int  = (unsigned int)(RH*512);
  // Serial.printf("RH = %f  RH_int = %d (0x%04X)\n", RH, RH_int , RH_int);
  bytes[0] = highByte(RH_int);
  bytes[1] = lowByte(RH_int);
  bytes[2] = highByte(T_int);
  bytes[3] = lowByte(T_int);
  write_multi_bytes(CCS_ENV_DATA,4,bytes);
}
