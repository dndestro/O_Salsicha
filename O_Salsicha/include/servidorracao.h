#include <Arduino.h>
#include <AsyncTCP.h>
#include <ESPAsyncWebServer.h>
#include <SPIFFS.h>

#ifndef ServidorRacao_h
#define ServidorRacao_h

class ServidorRacao{
    bool pgAtualizada = false;
    
    String destinatario = "celulardaempresa1935@gmail.com";  // endereços de email dos destinatários da mensagem
    String alarmeRacao = "3";                               // % do nível do recipiente de racao para envio do e-mail de alerta
    String alarmeAgua = "15";                              // % do nível do recipiente de água para envio do e-mail de alerta
    String racaoVazio = "10";
    String racaoCheio = "1";
    String aguaVazio = "10";
    String aguaCheio = "1";
    String botao = "";

    String nivelAgua;                                     // Nivel atual de água para ser exibido na 
    String nivelRacao;
    String distAgua;
    String distRacao;

    const char* DESTINATARIO = "destinatario";                // conterá os endereços de email dos destinatários da mensagem
    const char* ALARME_RACAO = "alarme_racao";                // conterá o limite do nível de ração
    const char* ALARME_AGUA = "alarme_agua";                 // conterá o limite do nível de água
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
        float getAguaVazio();
        float getAguaCheio();
        float getAlarmeRacao();
        float getAlarmeAgua();
        String getDestinatario();
        void setParametros(float racVaz, float racCheio, float aguVaz, float aguCheio, 
                           float almRacao, float almAgua, String dest);

    protected:
        String processar(const String& var);

    private:
         AsyncWebServer server;
};

#endif