#define ADAFRUIT_1918 11

namespace GUVA
{
    struct measurement
    {
        int value; // value: [0, 1023] = [0v, 5v]
    };

    measurement read(File &log_file)
    {
        auto reading = analogRead(ADAFRUIT_1918);
        log_file.print(reading);
        log_file.print("|");
        return {reading};
    }
}