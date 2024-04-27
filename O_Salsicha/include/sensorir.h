#include "Adafruit_VL53L0X.h"

#define ERROLEITURA 4

class SensorIR{
    Adafruit_VL53L0X cLox = Adafruit_VL53L0X ();

    public:
        SensorIR();
        uint8_t iniciaSensorIR();
        float getDistance();
};