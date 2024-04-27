#ifndef ULTRASSOM_
#include "ultrassom.h"
#endif

#define DISTAGUAVAZIO   0 // Distancia medida pelo sensor de ultrassom que representa que não há água
#define DISTAGUACHEIO   1   // Distancia medida pelo sensor de ultrassom que representa que não há água

#define PINOTRIGGER 5
#define PINOECHO    18

class Agua : Ultrassom{
    float nivelAgua = 0;
    uint8_t percMinAgua = 0;

    public:
        Agua();
        float getNivelAgua();

};