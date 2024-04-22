//#ifndef ARDUINO
#include <Arduino.h>
//#define ARDUINO
//#endif

#define DELAYTRIGGER    100
#define TIMEOUTPULSEIN  1000

class Ultrassom{
    uint8_t cPinoTrigger = 0;
    uint8_t cPinoEcho = 0;
    float cVelocidadeSom = 0;

    public:
        Ultrassom(uint8_t pinTrigger, uint8_t pinEcho, float velSom = 0.034);
        float getDistance();

};