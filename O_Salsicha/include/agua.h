#include "ultrassom.h"

#define PINOTRIGGER 5
#define PINOECHO    18

class Agua : public Ultrassom{
    float nivelAgua = 0;
    uint8_t percMinAgua = 0;
    float aguaVazio = 10;
    float aguaCheio = 1;

    public:
        Agua();
        float getNivelAgua();
        void setAguaVazio(float valor);
        void setAguaCheio(float valor);
};