/*
 * NTCThermistor.cpp 
 *     Thermistor NTC 
 */

#include "NTCThermistor.h"
#include <Arduino.h>

NTCThermistor::NTCThermistor(int pin, int numsamples)
{
  this->pin = pin;  
  this->numsamples = numsamples;
}

float NTCThermistor::getTemperature()
{
  uint8_t i;
  float average = 0, temp = 0;
  int samples[NUMSAMPLES];

  for (i = 0; i < numsamples; i ++ ) {
    samples[i] = analogRead(pin);
    delay(10);   
  }
  for (i = 0; i < numsamples; i ++) {
    average += samples[i];  
  }
  average /= numsamples;

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
