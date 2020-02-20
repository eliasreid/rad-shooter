#ifndef TIMER_H
#define TIMER_H

/*
 * Simple timer class
 * call Init with period for timed event
 * then call CheckTimeout to check if 'period' milliseconds
 * has passed since last occurence of event
 *
 * PauseSw() must be called when the game is paused / unpause
*/

#include <chrono>

class Timer
{
public:
  Timer();

  void Init(unsigned int period_ms, bool start_timedout = false);
  void setActive(bool is_active);
  bool getActive();
  void Reset(bool start_timedout = false);
  bool CheckTimeout();
  void PauseSw();

private:
  std::chrono::high_resolution_clock::time_point  prev_time_;
  std::chrono::high_resolution_clock::time_point::duration  saved_interval_;
  bool is_active_;
  bool is_paused_;
  bool is_init_;
  unsigned int period_ms_; // in milliseconds - could change type in constructor to duration?

  std::chrono::high_resolution_clock::time_point::duration GetTimeSincePrev();

};

#endif // TIMER_H
