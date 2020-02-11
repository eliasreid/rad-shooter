#include "timer.h"

Timer::Timer() : is_active_(false), is_init_(false), is_paused_(false)
{

}

void Timer::Init(unsigned int period_ms, bool is_active){
  is_init_ = true;
  period_ms_ = period_ms;
  is_active_ = is_active;
  if(is_active){
    //start timer
    prev_time_ = std::chrono::high_resolution_clock::now();
  }
}

void Timer::SetActive(bool is_active){
  if(is_init_){
    is_active_ = is_active;

    if(is_active == true){
      //start timer
      prev_time_ = std::chrono::high_resolution_clock::now();
    }
  }
}

bool Timer::CheckTimeout(){

  if(!is_active_ || is_paused_){
    return false;
  }

  bool ret;
  auto current_time = std::chrono::high_resolution_clock::now();
  unsigned int delta = std::chrono::duration_cast<std::chrono::milliseconds>(current_time-prev_time_).count();

  if(delta > period_ms_){
    prev_time_ = current_time;
    ret = true;
  } else{
    ret = false;
  }

  return ret;
}

void Timer::Reset(){
  if(is_active_){
    prev_time_ = std::chrono::high_resolution_clock::now();
  }
}

void Timer::PauseSw(){
  if(!is_active_){
    return;
  }

  is_paused_ = !is_paused_;
  if(is_paused_){
    //Timer was paused - Save current time since previous event
    saved_interval_ = GetTimeSincePrev();
  }else{
    //Timer was unpaused - restore state prior to pause with saved duration
    prev_time_ = std::chrono::high_resolution_clock::now() - saved_interval_;
  }
}

std::chrono::high_resolution_clock::time_point::duration Timer::GetTimeSincePrev(){
  auto current_time = std::chrono::high_resolution_clock::now();
  return current_time - prev_time_;
}
