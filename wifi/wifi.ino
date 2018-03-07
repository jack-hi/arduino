#include <SoftwareSerial.h>
#include <SerialESP8266wifi.h>

#define esp_uart_rx 2
#define esp_uart_tx 3
#define esp_rst_pin 4

SoftwareSerial espSerial(esp_uart_rx, esp_uart_tx); //Rx Tx

// init esp8266 wifi
SerialESP8266wifi wifi(espSerial, espSerial, esp_rst_pin, Serial);

void setup() {
  
  espSerial.begin(9600);

  Serial.begin(115200);
  while (!Serial)
    ;
  Serial.println("WiFi starting......");

  wifi.begin();

  wifi.connectToAP("TP-LINK_C2B3", "yy@212310429");
  wifi.setTransportToUDP();
  wifi.connectToServer("202.112.31.197", "123"); //NTP server
  
}

void loop() {
  //wifi.send(SERVER, "ESP8266 TEST");

}
