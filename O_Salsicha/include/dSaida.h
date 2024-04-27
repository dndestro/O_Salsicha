#include <Arduino.h>

class dSaida {
    uint8_t cPino;
    int cEstado;

    public:
        dSaida(uint8_t pinoSaida);
        byte setSaida(uint8_t valor);
        int getSaida();
        byte togSaida();
        void configPino(uint8_t pino);
};