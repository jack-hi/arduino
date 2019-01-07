/*
 * NTCThermistor： Get Temperature from NTC thermistor
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
#ifndef NTCThermistor_h
#define NTCThermistor_h

#include <Arduino.h>

#define THERMISTORNOMINAL 10000 //10K
#define TEMPERATURENOMINAL 25   //25'C
#define NUMSAMPLES 5 //take 5 samples
#define BCOEFFICIENT 3950 
#define SERIALRESISTOR 10000 //10K 

class NTCThermistor {
public:
  NTCThermistor(int pin, int numsamples = NUMSAMPLES);
  float getTemperature();
private:
  int pin;
  int numsamples;
  
};
#endif // NTCThermistor_h
