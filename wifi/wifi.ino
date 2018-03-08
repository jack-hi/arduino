#include <SoftwareSerial.h>
#include <SerialESP8266wifi.h>
#include <Wire.h>

#define esp_uart_rx 2
#define esp_uart_tx 3
#define esp_rst_pin 4

SoftwareSerial espSerial(esp_uart_rx, esp_uart_tx); //Rx Tx

// init esp8266 wifi
SerialESP8266wifi wifi(espSerial, espSerial, esp_rst_pin, Serial);



// AT24C256 eeprom 256K
class eepromAT24C256 {
private:
  TwoWire *i2c;
  uint8_t dev_addr;

public:
  eepromAT24C256(TwoWire *i2c_bus, uint8_t device_address) {
    i2c = i2c_bus;
    dev_addr = device_address;  
  }

  void write_byte(uint16_t addr, byte data) {
    i2c->beginTransmission(dev_addr);
    i2c->write((uint8_t)(addr >> 8));
    i2c->write((uint8_t)(addr & 0xFF));
    i2c->write((uint8_t)data);
    i2c->endTransmission();
    delay(50);
  }

  uint8_t read_byte(uint16_t addr) {
    uint8_t rdata = 0xFF;
    i2c->beginTransmission(dev_addr);
    i2c->write((uint8_t)(addr >> 8));
    i2c->write((uint8_t)(addr & 0xFF));
    i2c->endTransmission();  
    i2c->requestFrom(dev_addr, 1);
    if (i2c->available())
      rdata = i2c->read();

    return rdata;
  }
};
void setup() {
  
  espSerial.begin(9600);

  Serial.begin(9600);
  while (!Serial)
    ;

#if 1
  Serial.println("WiFi starting......");
  wifi.begin();

  wifi.connectToAP("TP-LINK_C2B3", "yy@212310429");
  wifi.setTransportToUDP();
  wifi.connectToServer("202.112.31.197", "123"); //NTP server
#endif

  /* AT24C256 EEPROM, Size: 256KB, Device address 0x50(0xA0>>1) */
  Wire.begin();
  
  eepromAT24C256 er(&Wire, 0x50);
  er.write_byte(0x0011, 0x11);
  
  Serial.print(er.read_byte(0x0011), HEX);

  
#if 0
  Wire.beginTransmission(0x50);
  Wire.write(0x00);
  Wire.write(0x08);
  Wire.write('H');
  Wire.endTransmission();

  delay(100);

  Wire.beginTransmission(0x50);
  Wire.write(0x00);
  Wire.write(0x08);
  Wire.endTransmission();
  
  Wire.requestFrom(0x50, 1);

  Serial.println("Read from AT24C02: ");
  byte r = Wire.read();
  Serial.print(r);
#endif
}

void loop() {
  //wifi.send(SERVER, "ESP8266 TEST");
 
}
