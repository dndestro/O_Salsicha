#include "servidorracao.h"

ServidorRacao::ServidorRacao() : server(80){
    
}

String ServidorRacao::processar(const String& var){
    
    if (var == "NIVELRACAO"){
        return lastNivelRacao;
    }
    
    else if (var == "DESTINATARIO"){
        return inputMessage1;
    }
    
    else if (var == "LIMITE_RACAO"){
        return inputMessage2;
    }
    
    else if (var == "LIMITE_AGUA")    {
        return inputMessage3;
    }
    return String();
}

void ServidorRacao::iniciaServidor(){
        
    if(!SPIFFS.begin(true)){
     
     while(1);
    }
    
    //REQUISICAO DA RAIZ
    server.on("/", HTTP_GET, [this](AsyncWebServerRequest * request){
         request->send(SPIFFS, "/index.html", String(), false, [this](const String& var){
             return this->processar(var);
         });
    });

    // REQUISICAO DA RAIZ PARA O ARQUIVO CSS
    server.on("/style.css", HTTP_GET, [](AsyncWebServerRequest *request){
        request->send(SPIFFS, "/style.css", "text/css");
    });

    // RECUPERA OS ATRIBUTOS DA PAGINS 
    server.on("/get", HTTP_GET, [this] (AsyncWebServerRequest * request){
    
    
    if (request->hasParam(PARAM_INPUT_1)) {   // Lê o endereço de e-mail digitado pelo usuário
      inputMessage1 = request->getParam(PARAM_INPUT_1)->value();
      
      if (request->hasParam(PARAM_INPUT_2)) { // Lê o limite do nível de ração setado pelo usuário para gerar alarme
        inputMessage2 = request->getParam(PARAM_INPUT_2)->value();
      }

      if (request->hasParam(PARAM_INPUT_3)){  // Lê o limite do nível de água setado pelo usuário para gerar alarme
        inputMessage3 = request->getParam(PARAM_INPUT_3)->value();
      }
    }
    else{
      inputMessage1 = "No message sent";
    }
    request->send(200, "text/html", "Dados enviados.<br><a href=\"/\">Voltar</a>");
  });
  
  server.onNotFound([this](AsyncWebServerRequest * request){
    request->send(404, "text/plain", "Not found");  
  });
 
  server.begin();
}