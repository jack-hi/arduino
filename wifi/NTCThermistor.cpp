/*
 * NTCThermistor.cpp 
 *     Thermistor NTC 
 */

#include "NTCThermistor.h"
#include <Arduino.h>

NTCThermistor::NTCThermistor(int pin)
{
  this->pin = pin;  
}

float NTCThermistor::getTemperature()
{
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
