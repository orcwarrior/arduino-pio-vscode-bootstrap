#ifndef EVENT_EMITTER_HPP
#define EVENT_EMITTER_HPP

#include <map>
#include <vector>
#include <string>
#include <stdio.h>
#include <iostream>
#include "./../callback.hpp"
#include "./Event/Event.hpp"
#include "./Event/TestEvent.hpp"

typedef util::Callback<void(Event *)> EventHandler;
using namespace std;

class Dog
{
public:
  string name;
  Dog(string name)
  {
    this->name = name;
  }
  void bark(Event *e)
  {
    TestEvent *test = (TestEvent *)e;
    printf("%s: Woof!!! %d\n", this->name.c_str(), test->val);
  }
};

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

public:
  EventManager()
  {
    this->events = new std::map<string, vector<EventHandler>>();
    this->defineEvent("test");
    this->addEventListener("notExistingEvent", BIND_FREE_CB(myEventHandler));

    Dog *doggo = new Dog("Doggo");
    this->addEventListener("notExistingEvent", BIND_MEM_CB(&Dog::bark, doggo));
    
    this->dispatchEvent("notExistingEvent", new TestEvent(666));

    // Serial.println((*this->events)[key][1]);
  };
  vector<EventHandler> *getEvent(string eventName)
  {
    if (this->events->find(eventName) != this->events->end())
    {
      return &this->events->at(eventName);
    }
    else
    {
      return NULL;
    }
  };

  void defineEvent(string eventName)
  {
    pair<string, vector<EventHandler>> newEvent(eventName, {});
    this->events->insert(newEvent);
    printf("Event name: %s created!\n", newEvent.first.c_str());
  }

  bool addEventListener(string eventName, EventHandler handler)
  {
    vector<EventHandler> *event = this->getEvent(eventName);
    if (!event)
    {
      this->defineEvent(eventName);
      return this->addEventListener(eventName, handler);
    }
    event->push_back(handler);
  }

  void dispatchEvent(string eventName, Event *e)
  {
    vector<EventHandler> *event = this->getEvent(eventName);
    for (auto const &eventHandler : *event)
    {
      eventHandler(e);
    }
  }
};

#endif