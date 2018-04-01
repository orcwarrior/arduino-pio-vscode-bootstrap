#include "./lib/callback.hpp"

#if defined(PLATFORM_IO)
#include "./main.platform.h"
#else
#include "./main.debug.h"
#endif

#include "./lib/IntervalManager/IntervalManager.hpp"
#include <iostream>
#include <stdio.h>

using util::Callback;

int ledState = 0;
void ledHandler(Event *e)
{
  ledState = !ledState;
  digitalWrite(LED_BUILTIN, ledState);
}

void ledInterval(Interval *i)
{
  // i->setInterval(i->getInterval()+2);
  ledState = !ledState;
  digitalWrite(LED_BUILTIN, ledState);
}

IntervalManager *intervalMan = IntervalManager::getInstance();
EventManager *man            = EventManager::getInstance();
void setup()
{
  pinMode(LED_BUILTIN, OUTPUT);
  man->addEventListener("test", BIND_FREE_CB(ledHandler));
}

void loop()
{
  intervalMan->run();
  man->dispatchEvent("test", new Event("test"));

  // eventMan->dispatchEvent("secondPassed", new Event("none"));
}