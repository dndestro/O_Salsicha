#include <Arduino.h>
#include "agua.h"
#include "racao.h"
#include "displayRacao.h"
#include "dSaida.h"
#include <WiFi.h>
#include "servidorracao.h"
#include <SPIFFS.h>
#include "emailracao.h"
#include "timer.h"
#include "botao.h"
#include <preferences.h>

#define MEDIA 20          //média para as leituras de água e ração. Deixa as leituras mais estáveis

#define PINOBTN    34     // Pino do botão
#define PINOLED     4     // D4 como saída de controle do Led

float nivelAgua = 0;
float distAgua = 0;
float nivelRacao = 0;
float distRacao = 0;
bool flagEmailenviado = false;
bool flagBtnLer = false;
String destinatario;

Botao btnLer(PINOBTN, INPUT_PULLUP, 30);     // sem Pull-up e 30ms de tempo de debounce
dSaida ledAlerta(PINOLED);
Agua agua;
Racao racao;
DisplayRacao display;
ServidorRacao servidor;
EmailRacao eMail;
Timer *timer5s = new Timer(5000);
Timer *timer500ms = new Timer(500);
Preferences eeprom;

//PARAMETROS DE WIFI E SERVIDOR
const char* ssid = "NeuesNetzwerk";
const char* password = "M1nh@N0v@r3d3";

//_____________________________________________________________________

void calcMedia(bool reseta){
  uint8_t i = 0;
  float totAgua = 0;
  float totDistAgua = 0;
  float totRacao = 0;
  float totDistRacao = 0;

  static uint8_t contador = 0;
  static bool primeiraContagem = true;

  static float tmpNivelAgua[MEDIA];
  static float tmpNivelRacao[MEDIA];
  static float tmpDistAgua[MEDIA];
  static float tmpDistRacao[MEDIA];

  if(reseta){
    primeiraContagem = true;
    contador = 0;
  }
  
  if(primeiraContagem){
    tmpNivelAgua[contador] = agua.getNivelAgua();
    tmpNivelRacao[contador] = racao.getNivelRacao();
    tmpDistAgua[contador] = agua.getDistance();
    tmpDistRacao[contador] = racao.getDistance();
    
    nivelAgua = tmpNivelAgua[contador];
    nivelRacao = tmpNivelRacao[contador];
    distAgua = tmpDistAgua[contador];
    distRacao = tmpDistRacao[contador];

    contador++;
    if(contador == MEDIA){
      primeiraContagem = false;
    }
  }
  
  else{

    for(i = 0; i < MEDIA; i++){
      totAgua = totAgua + tmpNivelAgua[i];
      totRacao = totRacao + tmpNivelRacao[i];
      totDistAgua = totDistAgua + tmpDistAgua[i];
      totDistRacao = totDistRacao + tmpDistRacao[i];
    }
    
    nivelAgua = totAgua / MEDIA;
    nivelRacao = totRacao / MEDIA;
    distAgua = totDistAgua / MEDIA;
    distRacao = totDistRacao / MEDIA;

    if(contador < (MEDIA - 1)){
      contador++;
    }
    else{
      contador = 0;
    }

    tmpNivelAgua[contador] = agua.getNivelAgua();
    tmpNivelRacao[contador] = racao.getNivelRacao();
    tmpDistAgua[contador] = agua.getDistance();
    tmpDistRacao[contador] = racao.getDistance();
  }

  //for(i = 0; i < MEDIA; i++){
    //Serial.print("Nivel Água ("); Serial.print(i); Serial.print("): "); Serial.println(tmpNivelAgua[i]);
    // Serial.print("Nivel Racao ("); Serial.print(i); Serial.print("): "); Serial.println(tmpNivelRacao[i]);
    // Serial.print("Dist Água  ("); Serial.print(i); Serial.print("): "); Serial.println(tmpDistAgua[i]);
    // Serial.print("Dist Racao("); Serial.print(i); Serial.print("): "); Serial.println(tmpDistRacao[i]);
  //}
  //Serial.println("____________________________________________________________");
}
//___________________________________________________________________



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

//________________________________________________________________________

// TIMER DE 5s
void fTimerTempo5s(){
  
  // nivelAgua = agua.getNivelAgua();
  // nivelRacao = racao.getNivelRacao();
  // distAgua = agua.getDistance();
  // distRacao = racao.getDistance();

  calcMedia(false);

  servidor.atualizaValores(nivelAgua, distAgua, nivelRacao, distRacao);
  display.atualizaLeituras(nivelRacao, nivelAgua);
  
  // Serial.print("Racao Cheio = "); Serial.println(servidor.getRacaoCheio());
  // Serial.print("Racao Vazio = "); Serial.println(servidor.getRacaoVazio());
  // Serial.print("Agua Cheio = "); Serial.println(servidor.getAguaCheio());
  // Serial.print("Agua Vazio = "); Serial.println(servidor.getAguaVazio());
}

//______________________________________________________________________

// TIMER DE 500ms
void fTimerTempo500ms(){
  if(flagEmailenviado){
    ledAlerta.togSaida();
  }
  else{
    ledAlerta.setSaida(LOW);
  }
}

//______________________________________________________________________

void ajustes(String botao){
  if(botao == "racmin"){
    racao.setRacaoVazio(servidor.getRacaoVazio());
    eeprom.putFloat("racaoVazio", servidor.getRacaoVazio());
    Serial.print("getRacaoVazio = "); Serial.println(servidor.getRacaoVazio());
  }

  if(botao == "racmax"){
    racao.setRacaoCheio(servidor.getRacaoCheio());
    eeprom.putFloat("racaoCheio", servidor.getRacaoCheio());
  }

  if(botao == "aguamin"){
    agua.setAguaVazio(servidor.getAguaVazio());
    eeprom.putFloat("aguaVazio", servidor.getAguaVazio());
  }

  if(botao == "aguamax"){
    agua.setAguaCheio(servidor.getAguaCheio());
    eeprom.putFloat("aguaCheio", servidor.getAguaCheio());
  }

  if(botao == "Alarme"){
    eeprom.putFloat("alarmeRacao", servidor.getAlarmeRacao());
    eeprom.putFloat("alarmeAgua", servidor.getAlarmeAgua());
    eeprom.putString("destinatario", servidor.getDestinatario());
  }
  servidor.atualizaValores(nivelAgua, distAgua, nivelRacao, distRacao);
}

//____________________________________________________________________


// FUNCAO DE SETUP
void setup() {
  float tmpRacaoVazio = 0;
  float tmpRacaoCheio = 0;
  float tmpAguaVazio = 0;
  float tmpAguaCheio = 0;
  float tmpAlarmeAgua = 0;
  float tmpAlarmeRacao = 0;
  String tmpDestinatario = "";
  
  Serial.begin(19200);
  delay(10);

  ledAlerta.setSaida(LOW);

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
  
  // ATUALIZA OS VALORES DE NÍVEL DE AGUA E RAÇÃO
  fTimerTempo5s();

  //CONFIGURAÇÃO DO EMAIL
  eMail.setFuncCallback(eMailCallback);
  //eMail.enviaEmail("celulardaempresa1935@gmail.com", "teste");

  //CONFIGURA O(S) TIMER(S)
  timer5s->setOnTimer(&fTimerTempo5s);
  timer5s->Start();

  timer500ms->setOnTimer(&fTimerTempo500ms);
  timer500ms->Start();

  eeprom.begin("limites", false);
  tmpRacaoVazio = eeprom.getFloat("racaoVazio", 25);
  tmpRacaoCheio = eeprom.getFloat("racaoCheio", 10);
  tmpAguaVazio = eeprom.getFloat("aguaVazio", 25);
  tmpAguaCheio = eeprom.getFloat("aguaCheio", 5);
  tmpAlarmeRacao = eeprom.getFloat("alarmeRacao", 3);
  tmpAlarmeAgua = eeprom.getFloat("alarmeAgua", 20);
  tmpDestinatario = eeprom.getString("destinatario", "celulardaempresa1935@gmail.com");
  servidor.setParametros(tmpRacaoVazio, tmpRacaoCheio, tmpAguaVazio, tmpAguaCheio,
                         tmpAlarmeRacao, tmpAlarmeAgua, tmpDestinatario);
  
  racao.setRacaoVazio(tmpRacaoVazio);
  racao.setRacaoCheio(tmpRacaoCheio);
  agua.setAguaVazio(tmpAguaVazio);
  agua.setAguaCheio(tmpAguaCheio);
  destinatario = tmpDestinatario;
}

//___________________________________________________________________________

void loop() {
  String bot = "";
  String mensagem = "";
  float alarmeAgua = servidor.getAlarmeAgua();
  float alarmeRacao = servidor.getAlarmeRacao();

  timer5s->Update();
  timer500ms->Update();

  // VERIFICA ESTA DO BOTÃO DE FORÇAR LEITURA
  if((!btnLer.getState()) && (!flagBtnLer)){
    Serial.println("Botao Ler");
    calcMedia(true);
    flagBtnLer = true;
  }
  else if((btnLer.getState()) && (flagBtnLer)){
    flagBtnLer = false;
  }
  
  // VERIFICA SE HOUVE ALGUM REQUEST NA PÁG WEB
  if(servidor.novoRequest()){
    bot = servidor.getBotao();
    Serial.println(bot);
    ajustes(bot);
  }
  
  // VERIFICA SE EXISTE ALARME ATIVO DE ÁGUA OU RAÇÃO
  // SE ALARME ATIVO, ENVIA E-MAIL E PISCA O LED DE ALERTA
  if((nivelAgua <= alarmeAgua) && !flagEmailenviado){
    flagEmailenviado = true;
    mensagem = "Au Au! Estou ficando sem água. Nível de água: " + String(nivelAgua, 0);
    eMail.enviaEmail(destinatario, mensagem);
  }
  else if((nivelRacao <= alarmeRacao) && !flagEmailenviado){
    flagEmailenviado = true;
    mensagem = "Au Au! Estou ficando sem ração. Nível de ração: " + String(nivelRacao, 0);
    eMail.enviaEmail(destinatario, mensagem);
  }
  else if((nivelAgua > alarmeAgua) && (nivelRacao > alarmeRacao) && flagEmailenviado){
    flagEmailenviado = false;
    mensagem = "Au Au! Obrigado por verificar a água e a ração. Nível de água: " + String(nivelAgua, 0) + 
                "Nível de Ração: " + String(nivelRacao, 0);
    eMail.enviaEmail(destinatario, mensagem);
  }
}