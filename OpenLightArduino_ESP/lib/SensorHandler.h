#include <Arduino.h>

class SensorHandler
{
 public:
  static double calcTemp();
  static void calculLight();

 private:
 
  // Disallow creating an instance of this object
  SensorHandler() {}
};