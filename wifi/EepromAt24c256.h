#ifndef EepromAt24c256_h
#define EepromAt24c256_h
// AT24C256 eeprom 256K

class EepromAt24c256 {
private:
  TwoWire *i2c;
  uint8_t dev_addr;

public: 
  EepromAt24c256(TwoWire *i2c_bus, uint8_t device_address);

  void write_byte(uint16_t addr, byte data);

  uint8_t read_byte(uint16_t addr);
};
#endif //EepromAt24c256_h  
