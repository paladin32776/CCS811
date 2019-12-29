# Interfaces with AMS's CCS811 CO2 and TVOC sensor
Reads CO2 and TVOC from the CCS811 sensor by Austria Micro Systems. Also allows readout of MfgID, DeviceID, and SerialID.

# Methods:

#### `CCS811()`

Constructor.

**IMPORTANT NOTE** - currently works for ESP8266 only due to specifics of Wire library.

#### `void get_serial_id(unsigned int* serial_id)`

Get serial number of CCS811. Arguments are:
- `serial_id` ... Pointer to array of unsigned ints of length 3. Serial number will be written into this array.

#### `unsigned int get_mfg_id()`

Get manufacturer ID.

#### `unsigned int get_device_id()`

Get device ID.

#### `void read(unsigned int* CO2, unsigned int* TVOC)`

Trigger measurements and retrieve temperature and humidity values. Arguments:
- `temperature` ... Pointer to float variable to store temperature value in.
- `humidity` ...  Pointer to float variable to store humidity value in.
