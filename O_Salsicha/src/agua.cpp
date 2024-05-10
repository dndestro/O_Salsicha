#include "agua.h"

Agua::Agua() : Ultrassom(PINOTRIGGER, PINOECHO){

}

float Agua::getNivelAgua(){
    float distancia = 0;

    distancia = getDistance();

    return ((aguaVazio - distancia) / (aguaVazio - aguaCheio) * 100); //retorna o percentual de água no recipiente com base na calibração
}

void Agua::setAguaVazio(float valor){
    aguaVazio = valor;
}

void Agua::setAguaCheio(float valor){
    if(valor != 0){
        aguaCheio = valor;
    }
    else{
        aguaCheio = 1000000;
    }
}