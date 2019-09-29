#include <Arduino.h>

class SensorHandler
{
 public:
  static double calcTemp();
  static String calcLight();

 private:
 
  // Disallow creating an instance of this object
  SensorHandler() {}
};