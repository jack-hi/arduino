#include <SoftwareSerial.h>
#include <SerialESP8266wifi.h>
#include <Wire.h>
#include "EepromAt24c256.h"


#define esp_uart_rx 2
#define esp_uart_tx 3
#define esp_rst_pin 4

SoftwareSerial espSerial(esp_uart_rx, esp_uart_tx); //Rx Tx

// init esp8266 wifi
SerialESP8266wifi wifi(espSerial, espSerial, esp_rst_pin, Serial);


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
  
  EepromAt24c256 er(&Wire, 0x50);
  er.write_byte(0x0011, 0x11);  
  
  Serial.print(er.read_byte(0x0011), HEX);

}

void loop() {
  //wifi.send(SERVER, "ESP8266 TEST");
 
}
