#include <Arduino.h>
#include "agua.h"
#include "racao.h"
#include "displayRacao.h"
#include "dSaida.h"
#include <WiFi.h>
//#include <AsyncTCP.h>
//#include <ESPAsyncWebServer.h>
#include "servidorracao.h"
#include "SPIFFS.h"

#define PINOLED     4               // D4 como saída de controle do Led

dSaida ledAlerta(PINOLED);
Agua agua;
Racao racao;
DisplayRacao display;
ServidorRacao servidor;

//PARAMETROS DE WIFI E SERVIDOR


const char* ssid = "NeuesNetzwerk";
const char* password = "M1nh@N0v@r3d3";

String inputMessage1 = "celulardaempresa1935@gmail.com";  // endereços de email dos destinatários da mensagem
String inputMessage2 = "3";                               // % do nível do recipiente de racao para envio do e-mail de alerta
String inputMessage3 = "15";                              // % do nível do recipiente de água para envio do e-mail de alerta
String lastNivelAgua;                                     // Nivel atual de água para ser exibido na 
String lastNivelRacao;

const char* PARAM_INPUT_1 = "destinatario";                // conterá os endereços de email dos destinatários da mensagem
const char* PARAM_INPUT_2 = "limite_racao";                // conterá o limite do nível de ração
const char* PARAM_INPUT_3 = "limite_agua";                 // conterá o limite do nível de água

//AsyncWebServer server(80);

// void notFound(AsyncWebServerRequest *request)
// {
//   request->send(404, "text/plain", "Not found");
// }


// String processor(const String& var)
// {
//   if (var == "NIVELRACAO")  {
//     return lastNivelRacao;
//   }
//   else if (var == "DESTINATARIO"){
//     return inputMessage1;
//   }
//   else if (var == "LIMITE_RACAO"){
//     return inputMessage2;
//   }
//   else if (var == "LIMITE_AGUA"){
//     return inputMessage3;
//   }
//   return String();
// }

void setup() {
  Serial.begin(9600);

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

  servidor.iniciaServidor();

   //server.begin();



}

//__________________________________________________________________________________

void loop() {

  // Serial.print("Nivel Agua = ");
  // Serial.println(agua.getNivelAgua());
  // delay(1500);

  // Serial.print("distancia IR = ");
  // Serial.println(racao.getNivelRacao());

  // display.atualizaLeituras(racao.getNivelRacao(), agua.getNivelAgua());
  // delay(1500);
}
