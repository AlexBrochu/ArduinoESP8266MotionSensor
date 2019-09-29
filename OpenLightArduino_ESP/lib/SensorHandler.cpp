#include "SensorHandler.h"

//TEMP Sensor
const int tempSensor = A0;
//Light sensor
const int lightSensor = A1;

double SensorHandler::calcTemp(){
  int sensorInput = analogRead(A0);
  double temp = (double)sensorInput / 1024;   //find percentage of input reading
  temp = temp * 5;                     //multiply by 5V to get voltage
  temp = temp - 0.5;                   //Subtract the offset 
  temp = temp * 100;
  return temp;
}

void SensorHandler::calculLight(){
  int light = analogRead(lightSensor);
  Serial.println(light); // print current light value
 
  if(light > 450) { // If it is bright...
      Serial.println("It is quite light!");
      digitalWrite(13,LOW); //turn left LED off
  }
  else if(light > 229 && light < 451) { // If it is average light...
      Serial.println("It is average light!");
      digitalWrite(13, HIGH); // turn left LED on
  }
  else { // If it's dark...
      Serial.println("It is pretty dark!");
      digitalWrite(13,HIGH); // Turn left LED on
  }
}
