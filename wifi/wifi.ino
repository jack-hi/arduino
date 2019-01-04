#include <SoftwareSerial.h>
#include <SerialESP8266wifi.h>
#include <Wire.h>
//#include "EEPROMAT24C256.h"

/*
 * Thermistor： Get Temperature from NTC thermistor
 * Reference: https://learn.adafruit.com/thermistor/using-a-thermistor
 * Connection: 
 *                  3.3V --------- AREF 
 *                    |
 *              SERIALRESISTOR(10K)
 *                    |
 *                    |-------- A0
 *                    |
 *                THERMISTOR
 *                    |
 *                   GND
 */
class Thermistor {
private:
  int pin; 
  
  static const int THERMISTORNOMINAL = 10000; // 10K
  static const int TEMPERATURENOMINAL = 25; // 25C
  static const int NUMSAMPLES = 5; 
  static const int BCOEFFICIENT = 3950;
  static const int SERIALRESISTOR = 10000; // 10K 

public:
  Thermistor(int pin) {
    this->pin = pin;  
    // connect AREF to 3.3V and use that as VCC, less noisy!
    analogReference(EXTERNAL);
  }  

  float getTemperature() {
    uint8_t i;
    float average = 0, temp = 0;
    int samples[NUMSAMPLES];

    for (i = 0; i < NUMSAMPLES; i ++ ) {
      samples[i] = analogRead(pin);
      delay(10);   
    }
    for (i = 0; i < NUMSAMPLES; i ++) {
      average += samples[i];  
    }
    average /= NUMSAMPLES;

    // convert the value to resistance
    average = 1023 / average - 1;
    average = SERIALRESISTOR / average;

    // convert to temperature
    temp = average / THERMISTORNOMINAL;
    temp = log(temp);
    temp /= BCOEFFICIENT;
    temp += 1.0 / (TEMPERATURENOMINAL + 273.15);
    temp = 1.0 / temp;
    temp -= 273.15;
    
    return temp;
  }
};

#define esp_uart_rx 2
#define esp_uart_tx 3
#define esp_rst_pin 4

SoftwareSerial espSerial(esp_uart_rx, esp_uart_tx); //Rx Tx

// init esp8266 wifi
//SerialESP8266wifi wifi(espSerial, espSerial, esp_rst_pin, Serial);
SerialESP8266wifi wifi(espSerial, espSerial, esp_rst_pin);

Thermistor thermistor(A0);
int ret = -1;

void setup() {
  
  espSerial.begin(9600);

  Serial.begin(9600);
  while (!Serial)
    ;

#if 1
  Serial.println("WiFi starting......");
  wifi.begin();

  wifi.connectToAP("TP-LINK_C2B3", "yy@212310429");
  //wifi.setTransportToUDP();
  //wifi.connectToServer("202.112.31.197", "123"); //NTP server
  //delay(10000);
  if (wifi.connectToServer("192.168.2.123", "41400")) {
    Serial.println("\nConnected to Server ----------");
    wifi.endSendWithNewline(false);
  }
 // wifi.send(SERVER, "ESP8266 TEST");
#endif

#if 0
  /* AT24C256 EEPROM, Size: 256KB, Device address 0x50(0xA0>>1) */
  Wire.begin();
  
  EEPROMAT24C256 er(&Wire, 0x50);
  er.write_byte(0x0011, 0x11);  
  
  Serial.print(er.read_byte(0x0011), HEX);
#endif

}

void loop() {
  
  float temp = thermistor.getTemperature();
  delay(3000);
  
  String ts = String(millis(), DEC) + ": " + "Thermistor: " +String(temp, 2) + "'C";
  wifi.send(SERVER, ts.c_str());

  delay(50); // delay > ~15ms
 
  //WifiMessage in = wifi.listenForIncomingMessage(5000); //timeout 5s
  WifiMessage in = wifi.getIncomingMessage();
  if (in.hasData) {
    //Serial.println(in.channel);
    Serial.println(in.message);  
  }




}
