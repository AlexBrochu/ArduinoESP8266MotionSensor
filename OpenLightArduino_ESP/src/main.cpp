#include <Arduino.h>
#include <SoftwareSerial.h>
#include "../lib/command.cpp"
#include "../lib/SensorHandler.cpp"

SoftwareSerial ESP_Serial(8,9); //Tx,Rx
String payload;
bool sendMsg = true;

// LED PIN
const byte LEDPIN=13;

void executeCommand(String msg){
  if(Command::isCommand(msg)){
    String command = Command::extractCommand(msg);
    if(command.indexOf("ON") != -1){
      //LED ON
      digitalWrite(LEDPIN, HIGH);  
    }
    if(command.indexOf("OFF") != -1){
      //LED OFF
      digitalWrite(LEDPIN, LOW);  
    }
  }
}

void setup() {
  pinMode(LEDPIN, OUTPUT);

  Serial.begin(9600);
  ESP_Serial.begin(9600);
  delay(2000);
}


void loop() {
  Serial.println("Current Temp: ");
  Serial.print(SensorHandler::calcTemp());
  SensorHandler::calculLight();

  if(sendMsg){
    // Write message to ESP8266
    ESP_Serial.write("test");
    Serial.println("sent");
    sendMsg = false;
  }

  if (ESP_Serial.available() > 0){
    // Read message to ESP8266
    payload = ESP_Serial.readString();
    executeCommand(payload);
    delay(1000);
  }
  Serial.println("done");
  delay(2000);
}