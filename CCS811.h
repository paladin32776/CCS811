#include "Arduino.h"
#include "I2C_COMM.h"

#define CCS_DEFAULT_ADDRESS 0x5A

#define CCS_STATUS 0x00
#define CCS_MEAS_MODE 0x01
#define CCS_ALG_RESULT_DATA 0x02
#define CCS_RAW_DATA 0x03
#define CCS_ENV_DATA 0x05
#define CCS_NTC 0x06
#define CCS_THRESHOLDS 0x10
#define CCS_BASELINE 0x11
#define CCS_HW_ID 0x20
#define CCS_HW_VERSION 0x21
#define CCS_FW_BOOT_VERSION 0x23
#define CCS_FW_APP_VERSION 0x24
#define CCS_ERROR_ID 0xE0
#define CSS_APP_START 0xF4
#define CCS_SW_RESET 0xFF

#define CCS_DATA_READY_MASK 0b00001000
#define CCS_ERROR_MASK 0b00000001
#define CCS_APP_VALID_MASK 0b00010000
#define CCS_FW_MODE_MASK 0b10000000

#define CCS_DRIVE_MODE_MASK 0b01110000
#define CCS_INT_DATARDY_MASK 0b00001000
#define CCS_INT_THRESH_MASK 0b00000100


class CCS811 : public I2C_COMM
{
  private:
    bool app_mode = false;
    bool running = false;
    unsigned char meas_mode=0;
    unsigned int CO2, TVOC;
    void init();
    unsigned char get_status();
    bool data_ready();
  public:
    CCS811();
    CCS811(unsigned char _addr);
    CCS811(unsigned char SDApin, unsigned char SCLpin);
    CCS811(unsigned char _addr, unsigned char SDApin, unsigned char SCLpin);
    bool iserror();
    void set_drive_mode(unsigned int drive_mode);
    unsigned int get_drive_mode();
    unsigned char get_hw_id();
    unsigned char get_hw_version();
    unsigned int get_fw_boot_version();
    unsigned char get_error_id();
    void read(unsigned int* _CO2, unsigned int* _TVOC);
    void set_env_data(float T, float RH);
};
