#include <SoftwareSerial.h>
#include <SerialESP8266wifi.h>
#include <Wire.h>

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

#if 0
  Serial.println("WiFi starting......");
  wifi.begin();

  wifi.connectToAP("TP-LINK_C2B3", "yy@212310429");
  wifi.setTransportToUDP();
  wifi.connectToServer("202.112.31.197", "123"); //NTP server
#endif

  /* AT24C02 EEPROM */
  Wire.begin();

  Wire.beginTransmission(0x50);
  Wire.write(0x0f);
  Wire.write(0x00);
  Wire.endTransmission();

  delay(1000);

  Wire.beginTransmission(0x50);
  Wire.write(0x0f);
  Wire.endTransmission();
  
  Wire.requestFrom(0x50, 1);

  Serial.println("Read from AT24C02: ");
  byte r = Wire.read();
  Serial.print(r, HEX);
}

void loop() {
  //wifi.send(SERVER, "ESP8266 TEST");
 
}
