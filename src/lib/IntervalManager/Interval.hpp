#ifndef INTERVAL_HPP
#define INTERVAL_HPP

#include "../callback.hpp"

class Interval;
typedef util::Callback<void(Interval *)> IntervalCallback;

class Interval
{
public:
  Interval(IntervalCallback cb, int interval)
  {
    this->callback = cb;
    this->interval = interval;
  }

  bool tryRun(long millis)
  {
    if (!this->nextRun || this->nextRun <= millis)
    {
      this->nextRun = millis + this->interval;
      this->callback(this);
      return true;
    }
    return false;
  }

  void setInterval(int newInterval) {
    const int intervalDiff = this->interval -  newInterval;
    this->nextRun -= intervalDiff;
    this->interval =  newInterval;
  }

  int getInterval() { return this->interval; }

private:
  int interval = 1000;
  int nextRun = 0; // so it'll run interval cb at the beggining
  IntervalCallback callback;
  
};

#endif