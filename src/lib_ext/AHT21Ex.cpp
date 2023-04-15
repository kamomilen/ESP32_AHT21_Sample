#include "AHT21Ex.h"
#include <Wire.h>

#ifdef AHT21_H
int AHT21Ex::readCelsius(float *pTemp, float *pHum, float *pHeat, bool pForceRead)
{
  int rError = AHT21::read(pTemp, pHum, pForceRead);
  if(rError == ESP_OK)
  {
    // [MIT license]
    // https://github.com/adafruit/DHT-sensor-library/blob/master/DHT.cpp
    float &rTe = *pTemp;
    float rTeF = rTe * 1.8 + 32; // DHT::convertCtoF
    float &rHu = *pHum;
    float rHi = 0.5 * (rTeF + 61.0 + ((rTeF - 68.0) * 1.2) + (rHu * 0.094));

    if (rHi > 79) {
        rHi = -42.379 + 2.04901523 * rTeF + 10.14333127 * rHu +
            -0.22475541 * rTeF * rHu +
            -0.00683783 * pow(rTeF, 2) +
            -0.05481717 * pow(rHu, 2) +
            0.00122874 * pow(rTeF, 2) * rHu +
            0.00085282 * rTeF * pow(rHu, 2) +
            -0.00000199 * pow(rTeF, 2) * pow(rHu, 2);

        if ((rHu < 13) && (rTeF >= 80.0) && (rTeF <= 112.0)) {
            rHi -= ((13.0 - rHu) * 0.25) * sqrt((17.0 - abs(rTeF - 95.0)) * 0.05882);
        } else if ((rHu > 85.0) && (rTeF >= 80.0) && (rTeF <= 87.0)) {
            rHi += ((rHu - 85.0) * 0.1) * ((87.0 - rTeF) * 0.2);
        }
    }

    // DHT::convertFtoC
    rHi = (rHi - 32) * 0.55555;

    rmAHT21OldHeat = rHi;
  }

  *pHeat = rmAHT21OldHeat;

  return(rError);
}
#endif