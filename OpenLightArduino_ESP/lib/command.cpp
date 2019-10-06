#include "command.h"

const String headerCommand = "C-";

bool Command::isCommand(String msg){
  int found = msg.indexOf(headerCommand);
  if (found!=-1){
    return true;
  }
  return false;
}

String Command::extractCommand(String msg){
  return msg.substring(headerCommand.length(), msg.length());
}