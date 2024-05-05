#include "emailracao.h"

EmailRacao::EmailRacao(){

}

void EmailRacao::setFuncCallback(sendStatusCallback func){
    smtpData.setSendCallback(func);
}

uint8_t EmailRacao::enviaEmail(String destinatario, String msg){
    // Set the SMTP Server Email host, port, account and password
    smtpData.setLogin(smtpServer, smtpServerPort, emailSenderAccount, emailSenderPassword);

    // Set the sender name and Email
    smtpData.setSender("Atunia", emailSenderAccount);

    // Set Email priority or importance High, Normal, Low or 1 to 5 (1 is highest)
    smtpData.setPriority("High");

    // Set the subject
    smtpData.setSubject(emailSubject);

    // Set the message with HTML format
    smtpData.setMessage(msg, true);

    // Add recipients
    smtpData.addRecipient(destinatario);

    //smtpData.setSendCallback(mCallback);

    // Start sending Email, can be set callback function to track the status
    if (!MailClient.sendMail(smtpData)){
        Serial.println("Error sending Email, " + MailClient.smtpErrorReason());
        return false;
    }
    // Clear all data from Email object to free memory
    smtpData.empty();
    return true;
}
