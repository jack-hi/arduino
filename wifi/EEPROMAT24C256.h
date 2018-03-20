#ifndef EEPROMAT24C256_h
#define EEPROMAT24C256_h
// AT24C256 eeprom 256K

#include <Arduino.h> 
#include <Wire.h>

class EEPROMAT24C256 {
private:
  TwoWire *i2c;      // I2C interface
  uint8_t dev_addr;

public: 
  /* i2c_bus must begin() first */
  EEPROMAT24C256(TwoWire *i2c_bus, uint8_t device_address);

  /* write a byte @addr */
  void write_byte(uint16_t addr, byte data);

  /* read a byte @addr */
  uint8_t read_byte(uint16_t addr);
};
#endif //EEPROMAT24C256_h  
