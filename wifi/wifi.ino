#include <SoftwareSerial.h>
#include <SerialESP8266wifi.h>
#include <Wire.h>
//#include "EEPROMAT24C256.h"
#include "NTCThermistor.h"

// Start ESP8266-01S 
#define esp_uart_rx 2
#define esp_uart_tx 3
#define esp_rst_pin 4
SoftwareSerial espSerial(esp_uart_rx, esp_uart_tx); //Rx Tx
//SerialESP8266wifi wifi(espSerial, espSerial, esp_rst_pin, Serial);
SerialESP8266wifi wifi(espSerial, espSerial, esp_rst_pin);

// 10K NTC Thermistor 
NTCThermistor thermistor(A0, 15);

void setup() {
  // WiFi init
  Serial.begin(9600);
  while (!Serial)
    ;
  espSerial.begin(9600);
  Serial.println("#WiFi starting...");
  wifi.begin();
  wifi.connectToAP("TP-LINK_C2B3", "yy@212310429");
  //wifi.setTransportToUDP();
  //wifi.connectToServer("202.112.31.197", "123"); //NTP server
  if (wifi.connectToServer("192.168.2.123", "41400")) {
    Serial.println("\n#Connected to Server.");
    wifi.endSendWithNewline(false);
  }

#if 0
  /* AT24C256 EEPROM, Size: 256Kbits, Device address 0x50(0xA0>>1) */
  Wire.begin();
  
  EEPROMAT24C256 er(&Wire, 0x50);
  er.write_byte(0x0011, 0x11);  
  
  Serial.print(er.read_byte(0x0011), HEX);
#endif

}

void loop() {
  float temp = thermistor.getTemperature();
  delay(3000);
  
  String ts = String(millis(), DEC) + ": " + "Temperature: " +String(temp, 2) + "'C";
  wifi.send(SERVER, ts.c_str());
  delay(50); // delay > ~15ms
  
  //WifiMessage in = wifi.listenForIncomingMessage(5000); //timeout 5s
  WifiMessage in = wifi.getIncomingMessage();
  if (in.hasData) {
    Serial.println(in.message);  
  }
}
