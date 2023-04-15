#include <Arduino.h>
#include <Wire.h>
#include <lib_ext/AHT21Ex.h>

typedef enum {
  SENSOR_AHT21_NONE,
  SENSOR_AHT21_OK
} Sensor_AHT21_Status_t;
Sensor_AHT21_Status_t sensorAHT21Status = SENSOR_AHT21_NONE;
AHT21Ex sensorAHT21(Wire);

float aht21Values[3][10];
int aht21ValuesIndex = 1;

void setup() {
  Serial.begin(115200); /* prepare for possible serial debug */

  // sensor
  #ifdef AHT21_H
  Wire.begin();
  if (sensorAHT21.begin()){
    printf("Failed to initialize AHT21.\n");
  } else {
    sensorAHT21Status = SENSOR_AHT21_OK;
    delay(100);
    float temp, hum, heat;
    int rError = sensorAHT21.read(&temp, &hum, &heat);
    for (int i = 0; i < 10; i++) {
      aht21Values[0][i] = temp;
      aht21Values[1][i] = hum;
      aht21Values[2][i] = heat;
    }
  }
  #endif
}

void sensorAHT21Read() {
  if (sensorAHT21Status == SENSOR_AHT21_OK) {
    float temp, hum, heat;
    int rError = sensorAHT21.readCelsius(&temp, &hum, &heat);
    printf(">Temperature(Now):%2.1f\n", temp);
    printf(">Humidity(Now):%2.1f\n", hum);
    printf(">HeatIndex(Now):%2.1f\n", heat);
    aht21Values[0][aht21ValuesIndex] = temp;
    aht21Values[1][aht21ValuesIndex] = hum;
    aht21Values[2][aht21ValuesIndex] = heat;
    if (aht21ValuesIndex < 9) {
      ++aht21ValuesIndex;
    } else {
      aht21ValuesIndex = 0;
    }
    delay(100);
    float tempSum, humSum, heatSum;
    for (int i = 0; i < 10; i++) {
      tempSum += aht21Values[0][i];
      humSum  += aht21Values[1][i];
      heatSum += aht21Values[2][i];
    }
    printf(">Temperature(Avg):%2.1f\n", tempSum / (float)10);
    printf(">Humidity(Avg):%2.1f\n", humSum / (float)10);
    printf(">HeatIndex(Avg):%2.1f\n", heatSum / (float)10);
  }
}

void loop() {
  sensorAHT21Read();
  delay(900);
}