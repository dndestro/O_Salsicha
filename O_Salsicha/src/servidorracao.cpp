#include "servidorracao.h"

ServidorRacao::ServidorRacao() : server(80){
    
}

String ServidorRacao::processar(const String& var){
    
    if (var == "NIVELAGUA"){
      return nivelAgua;
    }

    else if(var == "DISTAGUA"){
      return distAgua;
    }
    
    else if (var == "NIVELRACAO"){
      return nivelRacao;
    }

    else if(var == "DISTRACAO"){
      return distRacao;
    }
    
    else if (var == "DESTINATARIO"){
      return destinatario;
    }
    
    else if (var == "LIMITE_RACAO"){
      return limiteRacao;
    }
    
    else if (var == "LIMITE_AGUA"){
      return limiteAgua;
    }

    else if(var == "RACAO_VAZIO"){
      return racaoVazio;
    }

    else if(var == "RACAO_CHEIO"){
      return racaoCheio;
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
  
    
    if (request->hasParam(DESTINATARIO)) {   // Lê o endereço de e-mail digitado pelo usuário
      destinatario = request->getParam(DESTINATARIO)->value();
      
      if (request->hasParam(LIMITE_RACAO)) { // Lê o limite do nível de ração setado pelo usuário para gerar alarme
        limiteRacao = request->getParam(LIMITE_RACAO)->value();
      }

      if (request->hasParam(LIMITE_AGUA)){  // Lê o limite do nível de água setado pelo usuário para gerar alarme
        limiteAgua = request->getParam(LIMITE_AGUA)->value();
      }

      if(request->hasParam(BOTAO)){
        botao = request->getParam(BOTAO)->value();
      }
    }
    else if(request->hasParam(RAC_VAZIO)){
      racaoVazio = request->getParam(RAC_VAZIO)->value();

      if(request->hasParam(BOTAO)){
        botao = request->getParam(BOTAO)->value();
      }
    }

    else if(request->hasParam(RAC_CHEIO)){
      racaoCheio = request->getParam(RAC_CHEIO)->value();

      if(request->hasParam(BOTAO)){
        botao = request->getParam(BOTAO)->value();
      }
    }

    request->send(200, "text/html", "Dados enviados.<br><a href=\"/\">Voltar</a>");
    pgAtualizada = true;
  });
  
  server.onNotFound([this](AsyncWebServerRequest * request){
    request->send(404, "text/plain", "Not found");  
  });
 
  server.begin();
}

void ServidorRacao::atualizaValores(float nAgua, float dAgua, float nRacao, float dRacao){
  nivelAgua = String(nAgua, 2);
  distAgua = String(dAgua, 0);
  nivelRacao = String(nRacao, 2);
  distRacao = String(dRacao, 0);
}

String ServidorRacao::getBotao(){
  return botao;
}

bool ServidorRacao::novoRequest(){
  bool temp = pgAtualizada;
  pgAtualizada = false;
  return temp;
}

float ServidorRacao::getRacaoVazio(){
  float temp = atof(racaoVazio.c_str());
  return temp;
}

float ServidorRacao::getRacaoCheio(){
  float temp = atof(racaoCheio.c_str());
  return temp;
}