#include <ESP8266WebServer.h>
#include <ArduinoOTA.h>
#include "../lib/twilio.hpp"
#include "arduino_secrets.h"

// USE TEST config?
#define USE_TEST_CONFIG 1

// Find the api.twilio.com SHA1 fingerprint, this one was valid as 
// of August 2019.
const char fingerprint[] = "06 86 86 C0 A0 ED 02 20 7A 55 CC F0 75 BB CF 24 B1 D9 C0 49";

#if USE_TEST_CONFIG == 1
const char* account_sid = TEST_ACCOUNT_ID;
const char* auth_token = TEST_AUTHTOKEN;
String from_number = MAGIC_PHONE_FROM;
#else
const char* account_sid = LIVE_ACCOUNT_ID;
const char* auth_token = LIVE_AUTHTOKEN;
String from_number = PHONE_FROM;
#endif

const char* ssid = SECRET_SSID;
const char* password = SECRET_PASS;
// Details for the SMS we'll send with Twilio.  Should be a number you own 
// (check the console, link above).
String to_number    = PHONE_TO;
String message_body    = "Motion detected!!!";

// Optional - a url to an image.  See 'MediaUrl' here: 
// https://www.twilio.com/docs/api/rest/sending-messages
String media_url = "";

// The 'authorized number' to text the ESP8266 for our example
String master_number    = MASTER_PHONE_FROM;

// Global twilio objects
Twilio *twilio;
ESP8266WebServer twilio_server(8000);
#define swSer Serial

void sendMessage(){
  // Response will be filled with connection info and Twilio API responses
  // from this initial SMS send.
  String response;
  bool success = twilio->send_message(
    to_number,
    from_number,
    message_body,
    response,
    media_url
  );
  swSer.println(response);
}


/*
 * Setup function for ESP8266 Twilio Example.
 * 
 * Here we connect to a friendly wireless network, set the time, instantiate 
 * our twilio object, optionally set up software serial, then send a SMS 
 * or MMS message.
 */
void setup() {
  twilio = new Twilio(account_sid, auth_token, fingerprint);

  swSer.begin(9600);
  Serial.println("Booting");
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  while (WiFi.waitForConnectResult() != WL_CONNECTED) {
    Serial.println("Connection Failed! Rebooting...");
    delay(5000);
    ESP.restart();
  }

  ArduinoOTA.onStart([]() {
    Serial.println("Start");
  });
  ArduinoOTA.onEnd([]() {
    Serial.println("\nEnd");
  });
  ArduinoOTA.onProgress([](unsigned int progress, unsigned int total) {
    Serial.printf("Progress: %u%%\r", (progress / (total / 100)));
  });
  ArduinoOTA.onError([](ota_error_t error) {
    Serial.printf("Error[%u]: ", error);
    if (error == OTA_AUTH_ERROR) Serial.println("Auth Failed");
    else if (error == OTA_BEGIN_ERROR) Serial.println("Begin Failed");
    else if (error == OTA_CONNECT_ERROR) Serial.println("Connect Failed");
    else if (error == OTA_RECEIVE_ERROR) Serial.println("Receive Failed");
    else if (error == OTA_END_ERROR) Serial.println("End Failed");
  });
  ArduinoOTA.begin();
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    swSer.print(".");
  }
  swSer.println("");
  swSer.println("Connected to WiFi, IP address: ");
  swSer.println(WiFi.localIP());
}


/* 
 *  In our main loop, we listen for connections from Twilio in handleClient().
 */
void loop() {
  ArduinoOTA.handle();

  //Try reading from arduino
  String payload = Serial.readString();
  if(payload.length() > 0 && payload.equals("test")){
    swSer.println("C-ON");
    // Send message SMS
    // sendMessage();
  }
  delay(1000);
}