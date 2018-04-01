#ifndef EVENT_EMITTER_HPP
#define EVENT_EMITTER_HPP

#include "./../callback.hpp"
#include "./Event/Event.hpp"
#include "./Event/TestEvent.hpp"
#include <iostream>
#include <map>
#include <stdio.h>
#include <string>
#include <vector>

typedef util::Callback<void(Event *)> EventHandler;
using namespace std;

void myEventHandler(Event *e)
{
  TestEvent *test = (TestEvent *)e;
  // TestEvent* test = dynamic_cast<TestEvent*>(e);
  printf("EventHandler called!; val=%d\n", test->val);
}

class EventManager
{

private:
  std::map<std::string, vector<EventHandler>> *events;

  EventManager()
  {
    this->events = new std::map<string, vector<EventHandler>>();
  }
  EventManager(EventManager const &) = delete;
  void operator=(EventManager const &) = delete;

  void defineEvent(string eventName)
  {
    vector<EventHandler> blankVector;
    pair<string, vector<EventHandler>> newEvent(eventName, blankVector);
    this->events->insert(newEvent);
    printf("Event name: %s created!\n", newEvent.first.c_str());
  }

  // static EventManager instance;

public:
  static EventManager* getInstance()
  {
    static EventManager instance;
    return &instance;
  };

  // methods:
  vector<EventHandler> *getEvent(string eventName)
  {
    if (this->events->find(eventName) != this->events->end()) {
      return &(*this->events)[eventName];
    } else {
      return NULL;
    }
  };

  bool addEventListener(string eventName, EventHandler handler)
  {
    vector<EventHandler> *event = this->getEvent(eventName);
    if (!event) {
      this->defineEvent(eventName);
      return this->addEventListener(eventName, handler);
    }
    event->push_back(handler);
    return true;
  }

  void dispatchEvent(string eventName, Event *e)
  {
    vector<EventHandler> *event = this->getEvent(eventName);
    for (auto const &eventHandler : *event) {
      eventHandler(e);
    }
  }
};

#endif