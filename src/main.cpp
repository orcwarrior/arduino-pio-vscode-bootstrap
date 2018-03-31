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

EventManager* eventMan = new EventManager();
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
  eventMan->addEventListener("secondPassed", BIND_FREE_CB(ledHandler));
  Interval* i = new Interval(BIND_FREE_CB(ledInterval), 1000);
  intervalMan->add(i);
  intervalMan->add(new Interval(BIND_FREE_CB(ledInterval), 700));
  intervalMan->add(new Interval(BIND_FREE_CB(ledInterval), 1900));
}

void loop()
{
  intervalMan->run();
  // eventMan->dispatchEvent("secondPassed", new Event("none"));
}