#ifndef INTERVAL_HPP
#define INTERVAL_HPP

#include "../callback.hpp"

class Interval;
typedef util::Callback<void(Interval *)> IntervalCallback;

class Interval
{
public:
  Interval(IntervalCallback cb, int interval, bool once = false)
  {
    this->callback = cb;
    this->interval = interval;
    this->once = once;
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

  bool isOneTime() { return this->once; }

private:
  int interval = 1000;
  int nextRun = 0; // so it'll run interval cb at the beggining
  bool once; // run interval only one time (handled by manager)
  IntervalCallback callback;
  
};

#endif