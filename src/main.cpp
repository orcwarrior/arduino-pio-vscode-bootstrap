#include "./lib/callback.hpp"

#if defined(PLATFORM_IO)
#include "./main.platform.h"
#else
#include "./main.debug.h"
#endif

#include <stdio.h>
#include <iostream>
#include "./lib/IntervalManager/IntervalManager.hpp"

using util::Callback;

IntervalManager* intervalMan= new IntervalManager();

int ledState = 0;
void ledHandler(Event *e)
{
  ledState = !ledState;
  digitalWrite(LED_BUILTIN, ledState);
}

void ledInterval(Interval* i) {
  // i->setInterval(i->getInterval()+2);
  ledState = !ledState;
  digitalWrite(LED_BUILTIN, ledState);
}

void setup()
{
  pinMode(LED_BUILTIN, OUTPUT);
  EventManager* man = EventManager::getInstance();
  man->addEventListener("test", BIND_FREE_CB(ledHandler));
}

void loop()
{
  intervalMan->run();
  EventManager* man = EventManager::getInstance();
  man->dispatchEvent("test", new Event("test"));
  
  // eventMan->dispatchEvent("secondPassed", new Event("none"));
}