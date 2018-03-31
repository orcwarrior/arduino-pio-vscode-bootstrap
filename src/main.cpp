#include "./lib/callback.hpp"

#if defined(PLATFORM_IO)
#include "./main.platform.h"
#else
#include "./main.debug.h"
#endif

#include <stdio.h>
#include <iostream>

using util::Callback;

EventManager* eventMan = new EventManager();

int ledState = 0;
void ledHandler(Event *e)
{
  ledState = !ledState;
  digitalWrite(LED_BUILTIN, ledState);
}


void setup()
{
  pinMode(LED_BUILTIN, OUTPUT);
  eventMan->addEventListener("secondPassed", BIND_FREE_CB(ledHandler));
}

void loop()
{
  delay(1000);
  eventMan->dispatchEvent("secondPassed", new Event("none"));
}