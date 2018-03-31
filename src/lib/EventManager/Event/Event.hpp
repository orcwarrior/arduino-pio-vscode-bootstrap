#ifndef EVENT_HPP
#define EVENT_HPP

#include <string>

class Event
{
public:
  std::string type;

public:
  Event(std::string type)
  {
    this->type = type;
  };
};

#endif