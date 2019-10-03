#include "SensorHandler.h"

double SensorHandler::calcTemp(int tempSensor){
  int sensorInput = analogRead(tempSensor);
  double temp = (double)sensorInput / 1024;   //find percentage of input reading
  temp = temp * 5;                     //multiply by 5V to get voltage
  temp = temp - 0.5;                   //Subtract the offset 
  temp = temp * 100;
  return temp;
}

String SensorHandler::calcLight(int lightSensor){
  String msg;
  int light = analogRead(lightSensor);
  Serial.println(light); // print current light value
 
  if(light > 450) { // If it is bright...
    msg = "It is quite light!";
    digitalWrite(13,LOW); //turn left LED off
  }
  else if(light > 229 && light < 451) { // If it is average light...
    msg = "It is average light!";
    digitalWrite(13, HIGH); // turn left LED on
  }
  else { // If it's dark...
    msg = "It is pretty dark!";
     digitalWrite(13,HIGH); // Turn left LED on
  }
  return msg;
}

String SensorHandler::readMotion(int &state, byte pin, byte ledPin){
  int val = digitalRead(pin);
  String msg;
  if (val == HIGH) {            // check if the input is HIGH
    digitalWrite(ledPin, HIGH);  // turn LED ON
    if (state == LOW) {
      // we have just turned on
      msg="-ALERT-\n";
      msg.concat("Motion detected!");
      Serial.println(msg);
      // We only want to print on the output change, not state
      state = HIGH;
    }
  } else {
    digitalWrite(ledPin, LOW); // turn LED OFF
    if (state == HIGH){
      // we have just turned of
      msg="-ALERT-\n";
      msg.concat("Motion ended!");
      Serial.println(msg);
      // We only want to print on the output change, not state
      state = LOW;
    }
  }
  return msg;
}
