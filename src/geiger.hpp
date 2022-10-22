#include "def.hpp"
#include <RadiationWatch.h>

namespace RAD
{

  RadiationWatch geiger;
  int hitsSinceRead = 0;
  int noiseSinceRead = 0;

  void gammaCallback()
  {
    hitsSinceRead++;
  }

  void noiseCallback()
  {
    noiseSinceRead++;
  }

  void init()
  {
    geiger.setup();
    geiger.registerRadiationCallback(&gammaCallback);
    geiger.registerNoiseCallback(noiseCallback);
  }

  void read(File &log_file)
  {
    geiger.loop();

    log_file.print(geiger.radiationCount());
    log_file.print("|");
    log_file.print(geiger.cpm());
    log_file.print("|");
    log_file.print(geiger.uSvh());
    log_file.print("|");
    log_file.print(geiger.uSvhError());
    log_file.print("|");
    log_file.print(noiseSinceRead);
    log_file.print("|");

    noiseSinceRead = 0;
  }

}