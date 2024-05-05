#include "ESP32_MailClient.h"

#define emailSenderAccount    "destroautomacao@gmail.com"                       // conta criada para projetos de automação
#define emailSenderPassword   "cbwgaplvypcystls"                                // alternativa à senha da conta (pode ser um problema em alguns casos)
#define smtpServer            "smtp.gmail.com"                                  // servidor SMTP do Google
#define smtpServerPort        465                                               // porta do servidor SMTP
#define emailSubject          "Atunia diz: Olhar a ÁGUA e RAÇÃO do SALSICHA"    // Assunto do email enviado


typedef void (*minhaCallback)(SendStatus, void*);

class EmailRacao{
    
    private:
    SMTPData smtpData;
   
    public:
        EmailRacao();
        void setFuncCallback(sendStatusCallback func);
        uint8_t enviaEmail(String destinatario, String msg);
        static void mCallback(SendStatus msg, EmailRacao* inst);
};

