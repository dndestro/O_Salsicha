#include "Ultrassom.h"

Ultrassom::Ultrassom(uint8_t pinoTrigger, uint8_t pinoEcho, float velocidadeSom){
    cPinoTrigger = pinoTrigger;
    cPinoEcho = pinoEcho;
    cVelocidadeSom = velocidadeSom;
    pinMode(cPinoTrigger, OUTPUT);
    pinMode(cPinoEcho, INPUT);
}

float Ultrassom::getDistance(){
    uint32_t duracaoPulso = 0;

    digitalWrite(cPinoTrigger, HIGH);
    delayMicroseconds(DELAYTRIGGER);
    digitalWrite(cPinoTrigger, LOW);
    
    duracaoPulso = pulseIn(cPinoEcho, HIGH);//, TIMEOUTPULSEIN);
    return (duracaoPulso * cVelocidadeSom / 2); // if timeout retorna zero
}