#include <Arduino.h>
#include "Adafruit_BME680.h"

#define SEALEVELPRESSURE_HPA (1013.25)
#define MICS_5524 ??
#define ADAFRUIT_1918 ??
#define MICS_6814_NO2
#define MICS_6814_CO
#define MICS_6814_NH3

Adafruit_BME680 bme;

void setup()
{
  Serial.begin(9600);

  if (!bme.begin())
  {
    Serial.println("Could not detect BME680 sensor, please check wiring!");
    while (true)
      ;
  }

  bme.setTemperatureOversampling(BME680_OS_8X);
  bme.setHumidityOversampling(BME680_OS_2X);
  bme.setPressureOversampling(BME680_OS_4X);
  bme.setIIRFilterSize(BME680_FILTER_SIZE_3);
  bme.setGasHeater(320, 150); // 320*C for 150 ms
}

void loop()
{
  if (!bme.performReading())
  {
    Serial.println("Failed to perform reading :(");
    return;
  }
  Serial.print("Temperature = ");
  Serial.print(bme.temperature);
  Serial.println(" *C");

  Serial.print("Pressure = ");
  Serial.print(bme.pressure / 100.0);
  Serial.println(" hPa");

  Serial.print("Humidity = ");
  Serial.print(bme.humidity);
  Serial.println(" %");

  Serial.print("Gas = ");
  Serial.print(bme.gas_resistance / 1000.0);
  Serial.println(" KOhms");

  Serial.print("Approx. Altitude = ");
  Serial.print(bme.readAltitude(SEALEVELPRESSURE_HPA));
  Serial.println(" m");

  Serial.println();
  delay(2000);
}