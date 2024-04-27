#include <Arduino.h>
#include <AsyncTCP.h>
#include <ESPAsyncWebServer.h>
#include <SPIFFS.h>

#ifndef ServidorRacao_h
#define ServidorRacao_h

class ServidorRacao{
    String inputMessage1 = "celulardaempresa1935@gmail.com";  // endereços de email dos destinatários da mensagem
    String inputMessage2 = "3";                               // % do nível do recipiente de racao para envio do e-mail de alerta
    String inputMessage3 = "15";                              // % do nível do recipiente de água para envio do e-mail de alerta

    String lastNivelAgua;                                     // Nivel atual de água para ser exibido na 
    String lastNivelRacao;

    const char* PARAM_INPUT_1 = "destinatario";                // conterá os endereços de email dos destinatários da mensagem
    const char* PARAM_INPUT_2 = "limite_racao";                // conterá o limite do nível de ração
    const char* PARAM_INPUT_3 = "limite_agua";                 // conterá o limite do nível de água

    public:
        ServidorRacao();
        void iniciaServidor();

    protected:
        String processar(const String& var);

    private:
         AsyncWebServer server;
};

#endif