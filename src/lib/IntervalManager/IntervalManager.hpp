#ifndef INTERVAL_MANAGER_HPP
#define INTERVAL_MANAGER_HPP

#include "./Interval.hpp"
#include <string>
#include <vector>

using namespace std;

const int INITIAL_INTERVAL = 1000;
class IntervalManager
{
public:
  IntervalManager() {
    vector<Interval> initialVector;
    this->intervals = new vector<Interval>();
  }

  void add(Interval* i)
  {
    this->intervals->push_back(*i);
    this->updateShortestInterval(i);
  }
  void updateShortestInterval(Interval* i)
  {
    shortestInterval = (i->getInterval() < shortestInterval) ? i->getInterval() :shortestInterval;
  }
  bool remove(Interval* i)
  {
    int idx = 0;
    for (vector<Interval>::iterator it = intervals->begin();
         it != intervals->end(); ++it, ++idx) {
           Interval* curPtr = &(*this->intervals)[idx];
      if (curPtr == i) {
        printf("Interval found and removed! (%d)", idx);
        this->intervals->erase(it);
        this->recalculateShortestInterval();
        return true;
      }
    }
    return false;
  }

  void run()
  {
    long curMillis = millis();
    if (lastRun + shortestInterval <= curMillis) {
      for (int idx = 0; idx < intervals->size(); ++idx) {
        Interval* cur = &(*this->intervals)[idx];
        if (cur->tryRun(curMillis)) {
          if ( cur->isOneTime()) {
            this->remove(cur);
          }
          this->lastRun = curMillis;
        }
      }
    }
  }

private:
  vector<Interval>* intervals;
  int shortestInterval = INITIAL_INTERVAL;
  int lastRun = -147483647; // DK: So it'll always run intervals at the beginning
  void recalculateShortestInterval()
  {
    this->shortestInterval = INITIAL_INTERVAL;
    for (int idx = 0; idx <= intervals->size(); ++idx) {
      this->updateShortestInterval(&(*this->intervals)[idx]);
    }
  }
};

#endif