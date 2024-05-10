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
    
    else if (var == "ALARME_RACAO"){
      return alarmeRacao;
    }
    
    else if (var == "ALARME_AGUA"){
      return alarmeAgua;
    }

    else if(var == "RACAO_VAZIO"){
      return racaoVazio;
    }

    else if(var == "RACAO_CHEIO"){
      return racaoCheio;
    }

    else if(var == "AGUA_VAZIO"){
      return aguaVazio;
    }

    else if(var == "AGUA_CHEIO"){
      return aguaCheio;
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

    // RECUPERA OS ATRIBUTOS DA PAGINA 
    server.on("/get", HTTP_GET, [this] (AsyncWebServerRequest * request){
  
    // PARAMETROS DE ALARME
    if (request->hasParam(DESTINATARIO)) {   // Lê o endereço de e-mail digitado pelo usuário
      destinatario = request->getParam(DESTINATARIO)->value();
      
      if (request->hasParam(ALARME_RACAO)) { // Lê o limite do nível de ração setado pelo usuário para gerar alarme
        alarmeRacao = request->getParam(ALARME_RACAO)->value();
      }

      if (request->hasParam(ALARME_AGUA)){  // Lê o limite do nível de água setado pelo usuário para gerar alarme
        alarmeAgua = request->getParam(ALARME_AGUA)->value();
      }

      if(request->hasParam(BOTAO)){
        botao = request->getParam(BOTAO)->value();
      }
    }

    //PARAMETROS DE RAÇÃO
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

    else if(request->hasParam(AGUA_VAZIO)){
      aguaVazio = request->getParam(AGUA_VAZIO)->value();

      if(request->hasParam(BOTAO)){
        botao = request->getParam(BOTAO)->value();
      }
    }

    else if(request->hasParam(AGUA_CHEIO)){
      aguaCheio = request->getParam(AGUA_CHEIO)->value();

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
  distAgua = String(dAgua, 2);
  nivelRacao = String(nRacao, 2);
  distRacao = String(dRacao, 2);
}

String ServidorRacao::getBotao(){
  String temp = botao;
  botao = "";
  return temp;
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

float ServidorRacao::getAguaVazio(){
  float temp = atof(aguaVazio.c_str());
  return temp;
}

float ServidorRacao::getAguaCheio(){
  float temp = atof(aguaCheio.c_str());
  return temp;
}

float ServidorRacao::getAlarmeRacao(){
  float temp = atof(alarmeRacao.c_str());
  return temp;
}

float ServidorRacao::getAlarmeAgua(){
  float temp = atof(alarmeAgua.c_str());
  return temp;
}

String ServidorRacao::getDestinatario(){
  return destinatario;
}

void ServidorRacao::setParametros(float racVaz, float racCheio, 
                                  float aguVaz, float aguCheio,
                                  float almRacao, float almAgua,
                                  String dest){
  racaoVazio = String(racVaz, 0);
  racaoVazio.trim();

  racaoCheio = String(racCheio, 0);
  racaoCheio.trim();

  aguaVazio = String(aguVaz, 0);
  aguaVazio.trim();

  aguaCheio = String(aguCheio, 0);
  aguaCheio.trim();
  
  alarmeRacao = String(almRacao, 0);
  alarmeRacao.trim();

  alarmeAgua = String(almAgua, 0);
  alarmeAgua.trim();

  destinatario = dest;
  destinatario.trim();
}