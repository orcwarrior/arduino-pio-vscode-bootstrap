#ifndef EVENT_EMITTER_HPP
#define EVENT_EMITTER_HPP

#include <map>
#include <vector>
#include <string>
#include <stdio.h>
#include <iostream>
#include "./../callback.hpp"
#include "./Event.hpp"

typedef util::Callback<void (Event)> EventHandler;
using namespace std;

class EventManager
{
  private:
    std::map<string, vector<int>> *events;

  public:
    EventManager()
    {
      // this->events = new std::map<string, vector<int>>();
      string key = "test";
      (*this->events)[key] = {1, 2 };
      // printf(*this->events[key]); printf(", "); printf(*this->events[key][1]);

      // Serial.println((*this->events)[key][1]);
    };
};

#endif