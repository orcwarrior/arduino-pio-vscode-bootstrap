#ifndef TEST_EVENT_HPP
#define TEST_EVENT_HPP

#include <string>
#include "./Event.hpp"

class TestEvent : public Event
{
public:
  int val;
  TestEvent(int testVal) : Event("TestEvent")
  {
    this->val = testVal;
  };
};

#endif