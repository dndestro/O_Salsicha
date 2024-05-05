#include "racao.h"

Racao::Racao(){

}

uint8_t Racao::setupSensor(){
    return iniciaSensorIR();
}

float Racao::getNivelRacao(){
    float distancia = 0;

    distancia = getDistance();

    return ((racaoVazio - distancia) / (racaoVazio - racaoCheio) * 100); //retorna o percentual de água no recipiente com base na calibração
}

void Racao::setRacaoVazio(float valor){
    racaoVazio = valor;
    Serial.print("Racao Vazio = "); Serial.println(racaoVazio);
}

void Racao::setRacaoCheio(float valor){
    if( valor != 0){
        racaoCheio = valor;
    }
    else{
        racaoCheio = 1000000;
    }       
}