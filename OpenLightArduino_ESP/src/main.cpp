#include <Arduino.h>
#include <SoftwareSerial.h>
#include "../lib/command.cpp"
#include "../lib/SensorHandler.cpp"
#include <Timer.h>

SoftwareSerial ESP_Serial(8,9); //Tx,Rx
String payload;
bool sendMsg = true;

// LED PIN
const byte LED_PIN_LIGHT=13;

// PIR Sensor
const byte LED_PIR=12;
const byte PIR_INPUT=2;
int PIR_STATE = LOW;

//TEMP Sensor
const int tempSensor = A0;
//Light sensor
const int lightSensor = A1;

Timer t;

void canSend(){
  sendMsg = true;
}

void executeCommand(String msg){
  if(Command::isCommand(msg)){
    String command = Command::extractCommand(msg);
    if(command.indexOf("ON") != -1){
      //LED ON
      digitalWrite(LED_PIN_LIGHT, HIGH);  
    }
    if(command.indexOf("OFF") != -1){
      //LED OFF
      digitalWrite(LED_PIN_LIGHT, LOW);  
    }
  }
}

void setup() {
  pinMode(LED_PIN_LIGHT, OUTPUT);

  pinMode(PIR_INPUT, INPUT);
  pinMode(LED_PIR, OUTPUT);

  Serial.begin(9600);
  ESP_Serial.begin(9600);
  delay(2000);

  // every 10 min can send a message
  t.every(1000, canSend);
}


void loop() {
  // Update time
  t.update();
  String alert = SensorHandler::readMotion(PIR_STATE, PIR_INPUT, LED_PIR);
  Serial.println(alert);


  String body = "-MSG-\n";
  body += "Current Temp: " + String(SensorHandler::calcTemp(tempSensor),2) + "C*\n";
  body += "Current Light: " + SensorHandler::calcLight(lightSensor);
  Serial.println(body);

  if(sendMsg){
    if(body.length()>0){
      // Write message to ESP8266
      ESP_Serial.write(body.c_str()); 
    }
    if(alert.length()>0){
      ESP_Serial.write(alert.c_str());
    }
    Serial.println("sent");
    sendMsg = false;
  }

  if (ESP_Serial.available() > 0){
    // Read message from ESP8266
    payload = ESP_Serial.readString();
    executeCommand(payload);
    delay(1000);
  }
  Serial.println("done");
  delay(2000);
}