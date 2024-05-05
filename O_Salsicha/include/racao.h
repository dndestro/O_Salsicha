#include "sensorir.h"

class Racao : public SensorIR{
    float nivelRacao = 0;
    uint8_t percMinRacao = 0;
    float racaoVazio = 10;
    float racaoCheio = 1;

    public:
        Racao();
        uint8_t setupSensor();
        float getNivelRacao();
        void setRacaoVazio(float valor);
        void setRacaoCheio(float valor);
};