#include <Arduino.h>
#include <SoftwareSerial.h>

SoftwareSerial ESP_Serial(2,3); //Tx,Rx
const String headerCommand = "C-";
String payload;

// LED PIN
const byte LEDPIN=13;

bool isCommand(String msg){
  int found = msg.indexOf(headerCommand);
  if (found!=-1){
    return true;
  }
  return false;
}

String extractCommand(String msg){
  return msg.substring(headerCommand.length(), msg.length());
}

void executeCommand(String msg){
  if(isCommand(msg)){
    String command = extractCommand(msg);
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
  while (ESP_Serial.available() > 0){
    payload = ESP_Serial.readString();
    executeCommand(payload);
    delay(1000);
  }
}