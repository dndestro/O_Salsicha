#include <Arduino.h>
#include "agua.h"
#include "racao.h"
#include "displayRacao.h"
#include "dSaida.h"
#include <WiFi.h>
#include "servidorracao.h"
#include "SPIFFS.h"
#include "emailracao.h"
#include "timer.h"

#define PINOLED     4               // D4 como saída de controle do Led

float nivelAgua = 0;
float distAgua = 0;
float nivelRacao = 0;
float distRacao = 0;

dSaida ledAlerta(PINOLED);
Agua agua;
Racao racao;
DisplayRacao display;
ServidorRacao servidor;
EmailRacao eMail;
Timer *timer5s = new Timer(5000);

//PARAMETROS DE WIFI E SERVIDOR
const char* ssid = "NeuesNetzwerk";
const char* password = "M1nh@N0v@r3d3";


// CALLBACK DE EMAIL
void eMailCallback(SendStatus msg){
  Serial.println("Passou pela função de CallBack de e-mail");
  // Print the current status
  Serial.println(msg.info());

  // Do something when complete
  if (msg.success()) {
    Serial.println("----------------");
  }
}

// CALBACK DO TEMPORRIZADOR
void fTimerTempoCiclo(){
  nivelAgua = agua.getNivelAgua();
  distAgua = agua.getDistance();
  nivelRacao = racao.getNivelRacao();
  distRacao = racao.getDistance();
  servidor.atualizaValores(nivelAgua, distAgua, nivelRacao, distRacao);
  display.atualizaLeituras(nivelRacao, nivelAgua);
  
  Serial.print("Racao Cheio = "); Serial.println(servidor.getRacaoCheio());
  Serial.print("Racao Vazio = "); Serial.println(servidor.getRacaoVazio());
}

void ajustes(String botao){
  if(botao == "racmin"){
    racao.setRacaoVazio(servidor.getRacaoVazio());
  }

  if(botao == "racmax"){
    racao.setRacaoCheio(servidor.getRacaoCheio());
  }
}

void setup() {
  Serial.begin(9600);
  delay(10);

//INICIALIZAÇÃO DO DISPLAY
  if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)){
    Serial.println("SSD1306 allocation failed");
    ledAlerta.setSaida(HIGH); // Se o disply falhar, acende o led para sinalizar a falha
    while(1);
  }

//INICIALIZAÇÃO DO SENSOR DA RACAO
  if(!racao.setupSensor()){
    Serial.println("Falha Sensor Racao");
    display.msgCustomizada("Falha Sensor IR", TXTPEQ);
    while(1);
  }
  
// MENSAGEM DE SPLASH
  display.msgSplash();

// // INICIALIZAÇÃO DO WIFI
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  if (WiFi.waitForConnectResult() != WL_CONNECTED)
  {
    Serial.println("Falha no Wifi!");
    display.msgCustomizada("FALHA WIFI", TXTGRD);
    while(1);
  }
  else{
    Serial.println(WiFi.localIP());
    display.msgCustomizada("END. IP", TXTGRD);
    display.msgCustomizada(WiFi.localIP(), TXTGRD, 0, 30, false);
    delay(5000);
  }

  //INICIA SERVIDOR WEB
  servidor.iniciaServidor();
  fTimerTempoCiclo();          //Atualiza os valores para apágina web

  //CONFIGURAÇÃO DO EMAIL
  eMail.setFuncCallback(eMailCallback);
  //eMail.enviaEmail("celulardaempresa1935@gmail.com", "teste");

  //CONFIGURA O(S) TIMER(S)
  timer5s->setOnTimer(&fTimerTempoCiclo);
  timer5s->Start();
}

//__________________________________________________________________________________

void loop() {
  String bot = "";
  float valor = 0;

  if(servidor.novoRequest()){
    bot = servidor.getBotao();
    Serial.println(bot);
    ajustes(bot);
  }
  timer5s->Update();
}