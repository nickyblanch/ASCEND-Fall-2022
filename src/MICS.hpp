
namespace MICS
{
#define MICS_6814_NO2 11
#define MICS_6814_CO 11
#define MICS_6814_NH3 11
#define MICS_5524_VOC 11
#define MICS_5524_EN 11

    struct measurement
    {
        int VOC;
        int NO2;
        int CO;
        int NH3;
    };

    measurement read(File &log_file)
    {
        measurement r{
            analogRead(MICS_5524_VOC),
            analogRead(MICS_6814_NO2),
            analogRead(MICS_6814_CO),
            analogRead(MICS_6814_NH3)};

        log_file.print(r.VOC);
        log_file.print("|");
        log_file.print(r.NO2);
        log_file.print("|");
        log_file.print(r.CO);
        log_file.print("|");
        log_file.print(r.NH3);
        log_file.print("|");

        return r;
    }

}