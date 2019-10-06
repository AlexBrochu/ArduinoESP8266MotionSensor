#include <Arduino.h>

class Command
{
 public:
  static bool isCommand(String msg);
  static String extractCommand(String msg);

 private:
 
  // Disallow creating an instance of this object
  Command() {}
};