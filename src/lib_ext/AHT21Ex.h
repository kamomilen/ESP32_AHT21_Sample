#include "AHT21.h"
#include <Wire.h>
#ifdef AHT21_H
class AHT21Ex : public AHT21
{
public:
    AHT21Ex() : AHT21::AHT21(){};
    AHT21Ex(TwoWire &i2c) : AHT21::AHT21(i2c){};
    int readCelsius(float *pTemp, float *pHum, float *pHeat, bool pForceRead = false);
private:
    float rmAHT21OldHeat;
};
#endif