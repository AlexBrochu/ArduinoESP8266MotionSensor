/* Gsender class helps send e-mails from Gmail account
*  using Arduino core for ESP8266 WiFi chip
*  by Boris Shobat
*  September 29 2016
*/
#ifndef G_SENDER
#define G_SENDER
#define GS_SERIAL_LOG_1         // Print to Serial only server responce
#define GS_SERIAL_LOG_2       //  Print to Serial client commands and server responce
#include <ESP8266WiFi.h>
#include "arduino_secrets.h"

class Gsender
{
    protected:
        Gsender();
    private:
        const int SMTP_PORT = 2525;
        const char* SMTP_SERVER = "mail.smtp2go.com";
        const char* EMAILBASE64_LOGIN = EMAIL_BASE64;
        const char* EMAILBASE64_PASSWORD = PASSWORD_BASE64;
        const char* FROM = EMAIL_FROM;
        const char* _error = nullptr;
        char* _subject = nullptr;
        String _serverResponce;
        static Gsender* _instance;
        bool AwaitSMTPResponse(WiFiClient &client, const String &resp = "", uint16_t timeOut = 10000);

    public:
        static Gsender* Instance();
        Gsender* Subject(const char* subject);
        Gsender* Subject(const String &subject);
        bool Send(const String &to, const String &message);
        String getLastResponce();
        const char* getError();
};
#endif // G_SENDER
