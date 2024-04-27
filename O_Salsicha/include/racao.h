#include "sensorir.h"

#define DISTRACAOVAZIO   0 // Distancia medida pelo sensor de IR que representa que não há racao
#define DISTRACAOCHEIO   1   // Distancia medida pelo sensor de IR que representa que não há racao

class Racao : SensorIR{
    float nivelRacao = 0;
    uint8_t percMinRacao = 0;

    public:
        Racao();
        uint8_t setupSensor();
        float getNivelRacao();
};