#include "./dummyLibs/Arduino.h"
#include <stdio.h>
#include "./lib/EventManager/EventManager.hpp"

void setup(void);
void loop(void);
int main()
{
  const char* str = "Hi debugger, whatsapp?";
  setup();
  while(true) {loop();}
}