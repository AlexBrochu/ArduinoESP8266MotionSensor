#include <Arduino.h>

class SensorHandler
{
 public:
  static double calcTemp(int tempSensor);
  static String calcLight(int lightSensor);
  static String readMotion(int &state, byte pin, byte ledPin);

 private:
 
  // Disallow creating an instance of this object
  SensorHandler() {}
};