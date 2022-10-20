#include "ICM_20948.h"

namespace ICM
{
    struct vec
    {
        float x;
        float y;
        float z;
    };

    struct measurement
    {
        vec acc;
        vec gyr;
        vec mag;
    };

    ICM_20948_I2C icm;

    void init()
    {
        bool initialized = false;
        int tries = 0;
        while (!initialized && tries < 10)
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
            tries++;
        }
    }

    measurement read(File &log_file)
    {
        if (icm.dataReady())
        {
            icm.getAGMT();
            delay(30);

            measurement r{
                {icm.accX(), icm.accY(), icm.accZ()},
                {icm.gyrX(), icm.gyrY(), icm.gyrZ()},
                {icm.magX(), icm.magY(), icm.magZ()}};

            log_file.print(r.acc.x, 3);
            log_file.print("|");
            log_file.print(r.acc.y, 3);
            log_file.print("|");
            log_file.print(r.acc.z, 3);
            log_file.print("|");
            log_file.print(r.gyr.x, 3);
            log_file.print("|");
            log_file.print(r.gyr.y, 3);
            log_file.print("|");
            log_file.print(r.gyr.z, 3);
            log_file.print("|");
            log_file.print(r.mag.x, 3);
            log_file.print("|");
            log_file.print(r.mag.y, 3);
            log_file.print("|");
            log_file.print(r.mag.z, 3);
            log_file.print("|");

            return r;
        }
        else
        {
            Serial.println("ICM Data Not Ready!!!");
            log_file.print("N|N|N|N|N|N|N|N|N|");
            return {};
        }
    }
}