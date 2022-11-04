#include "Adafruit_BME680.h"
#include "def.hpp"

Adafruit_BME680 bme;

#define SEALEVELPRESSURE_HPA (1013.25)

namespace BME
{
    struct measurement
    {
        float temp;     // *C
        uint32_t pres;  // Pa
        float hum;      // %
        float gas_res;  // KOhm
        float altitude; // Meters
    };

    void init()
    {
        int i = 0;
        bool inited = false;
        while (!inited && i < 5)
        {
            if (bme.begin())
            {
                inited = true;
                Serial.println("BME680 Initialized");
                digitalWrite(LED_PIN, HIGH);
            }
            else
            {
                Serial.println("Could not detect BME680 sensor, please check wiring!");
                digitalWrite(LED_PIN, LOW);
                delay(500);
            }
            i++;
        }

        bme.setTemperatureOversampling(BME680_OS_8X);
        bme.setHumidityOversampling(BME680_OS_2X);
        bme.setPressureOversampling(BME680_OS_4X);
        bme.setIIRFilterSize(BME680_FILTER_SIZE_3);
        bme.setGasHeater(320, 150); // 320*C for 150 mss
    }

    measurement read(File &log_file)
    {
        if (!bme.performReading())
        {
            Serial.println("Failed to perform reading :(");
            log_file.print("N,N,N,N,N,");
            return {};
        }

        log_file.print(bme.temperature);
        log_file.print(",");
        log_file.print(bme.pressure);
        log_file.print(",");
        log_file.print(bme.humidity);
        log_file.print(",");
        log_file.print(bme.gas_resistance / 1000.0);
        log_file.print(",");
        log_file.print(bme.readAltitude(SEALEVELPRESSURE_HPA));
        log_file.print(",");

        return {
            bme.temperature,
            bme.pressure,
            bme.humidity,
            bme.gas_resistance / 1000.0,
            bme.readAltitude(SEALEVELPRESSURE_HPA)};
    }
}