#include "racao.h"

Racao::Racao(){

}

uint8_t Racao::setupSensor(){
    return iniciaSensorIR();
}

float Racao::getNivelRacao(){
    float distancia = 0;

    distancia = getDistance();

    return ((distancia - DISTRACAOVAZIO) / DISTRACAOCHEIO * 100); //retorna o percentual de água no recipiente com base na calibração
}