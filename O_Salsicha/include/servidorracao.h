#include <Arduino.h>
#include <AsyncTCP.h>
#include <ESPAsyncWebServer.h>
#include <SPIFFS.h>

#ifndef ServidorRacao_h
#define ServidorRacao_h

class ServidorRacao{
    bool pgAtualizada = false;
    
    String destinatario = "celulardaempresa1935@gmail.com";  // endereços de email dos destinatários da mensagem
    String limiteRacao = "3";                               // % do nível do recipiente de racao para envio do e-mail de alerta
    String limiteAgua = "15";                              // % do nível do recipiente de água para envio do e-mail de alerta
    String racaoVazio = "0";
    String racaoCheio = "1";
    String aguaVazio = "0";
    String aguaCheio = "1";
    String botao = "";

    String nivelAgua;                                     // Nivel atual de água para ser exibido na 
    String nivelRacao;
    String distAgua;
    String distRacao;

    const char* DESTINATARIO = "destinatario";                // conterá os endereços de email dos destinatários da mensagem
    const char* LIMITE_RACAO = "limite_racao";                // conterá o limite do nível de ração
    const char* LIMITE_AGUA = "limite_agua";                 // conterá o limite do nível de água
    const char* BOTAO = "botao";
    const char* RAC_VAZIO = "racao_vazio";
    const char* RAC_CHEIO = "racao_cheio";
    const char* AGUA_VAZIO = "agua_vazio";
    const char* AGUA_CHEIO = "agua_cheio";

    public:
        ServidorRacao();
        void iniciaServidor();
        void atualizaValores(float nAgua, float dAgua, float nRacao, float dRacao);
        String getBotao();
        bool novoRequest();
        float getRacaoVazio();
        float getRacaoCheio();

    protected:
        String processar(const String& var);

    private:
         AsyncWebServer server;
};

#endif