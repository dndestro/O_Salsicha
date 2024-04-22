#include <Arduino.h>
#include "ultrassom.h"
#include "sensorir.h"

#define PINOTRIGGER 5
#define PINOECHO    18


Ultrassom uSom(PINOTRIGGER, PINOECHO);
//SensorIR sensorIR;

void setup() {
  Serial.begin(9600);
  // if(!sensorIR.iniciaSensorIR()){
  //   Serial.println("Falha Sensor IR");
  //   while(1);
  // }
}

void loop() {
  Serial.print("Distancia = ");
  Serial.println(uSom.getDistance());
  delay(1500);

  // Serial.print("distancia IR = ");
  // Serial.println(sensorIR.getDistance());
  // delay(1500);
}
