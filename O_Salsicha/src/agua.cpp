#include "agua.h"

Agua::Agua() : Ultrassom(PINOTRIGGER, PINOECHO){

}

float Agua::getNivelAgua(){
    float distancia = 0;

    distancia = getDistance();

    return ((distancia - DISTAGUAVAZIO) / DISTAGUACHEIO * 100); //retorna o percentual de água no recipiente com base na calibração
}