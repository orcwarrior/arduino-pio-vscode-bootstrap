#include "./lib/callback.hpp"

#if defined(PLATFORM_IO)
#include "./main.platform.h"
#else
#include "./main.debug.h"
#endif

#include <stdio.h>
#include <iostream>

using util::Callback;

void setup() {
  pinMode(LED_BUILTIN, OUTPUT);
}

void ledOnHandler() {
  delay(30);
//   // turn the LED off by making the voltage LOW
  digitalWrite(LED_BUILTIN, LOW);
   // wait for a second
}
void loop()
{
  // turn the LED on (HIGH is the voltage level)
  digitalWrite(LED_BUILTIN, HIGH);
  delay(400);
  digitalWrite(LED_BUILTIN, LOW);
  delay(150);
  // Callback<void()> ledCb = BIND_FREE_CB(&ledOnHandler);
  // ledCb();
}