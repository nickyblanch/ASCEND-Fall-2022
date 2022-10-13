#include <Arduino.h>
#include "Adafruit_BME680.h"
#include "ICM_20948.h"

#define SEALEVELPRESSURE_HPA (1013.25)
#define MICS_5524 11
#define ADAFRUIT_1918 11
#define MICS_6814_NO2 11
#define MICS_6814_CO 11
#define MICS_6814_NH3 11

Adafruit_BME680 bme;
ICM_20948_I2C icm;

void setup()
{
  Serial.begin(9600);
  Wire.begin();
  Wire.setClock(400000);

  bool initialized = false;
  while (!initialized)
  {
    icm.begin(Wire);

    Serial.print(F("Initialization of the sensor returned: "));
    Serial.println(icm.statusString());
    if (icm.status != ICM_20948_Stat_Ok)
    {
      Serial.println("Trying again...");
      delay(500);
    }
    else
    {
      initialized = true;
    }
  }

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
  if (icm.dataReady())
  {
    icm.getAGMT();
    delay(30);

    char *line;
    sprintf(line, "Acc (mg) {x: %.5f, y: %.5f, z: %.5f}", icm.accX(), icm.accY(), icm.accZ());
    sprintf(line, "Gyr (dps) {x: %.5f, y: %.5f, z: %.5f}", icm.gyrX(), icm.gyrY(), icm.gyrZ());
    sprintf(line, "Mag (uT) {x: %.5f, y: %.5f, z: %.5f}", icm.magX(), icm.magY(), icm.magZ());
  }
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

  Serial.print("VOC: ");
  Serial.println(analogRead(MICS_5524));

  Serial.print("NO2: ");
  Serial.println(analogRead(MICS_6814_NO2));

  Serial.print("CO: ");
  Serial.println(analogRead(MICS_6814_CO));

  Serial.print("NH3: ");
  Serial.print(analogRead(MICS_6814_NH3));

  delay(2000);
}