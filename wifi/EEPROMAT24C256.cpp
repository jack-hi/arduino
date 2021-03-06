#include "EEPROMAT24C256.h"

EEPROMAT24C256::EEPROMAT24C256(TwoWire *i2c_bus, uint8_t device_address) {
  i2c = i2c_bus;
  dev_addr = device_address;  
}

void EEPROMAT24C256::write_byte(uint16_t addr, byte data) {
  i2c->beginTransmission(dev_addr);
  i2c->write((uint8_t)(addr >> 8));
  i2c->write((uint8_t)(addr & 0xFF));
  i2c->write((uint8_t)data);
  i2c->endTransmission();
  delay(50);
}

uint8_t EEPROMAT24C256::read_byte(uint16_t addr) {
  uint8_t rdata = 0xFF;
  i2c->beginTransmission(dev_addr);
  i2c->write((uint8_t)(addr >> 8));
  i2c->write((uint8_t)(addr & 0xFF));
  i2c->endTransmission();  
  i2c->requestFrom((int)dev_addr, 1);
  if (i2c->available())
    rdata = i2c->read();

  return rdata;
}
