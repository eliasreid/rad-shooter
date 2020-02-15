#include <iostream>
#include "subject.h"

void Subject::AddObserver(Observer* new_observer){
  if(std::find(observers_.begin(), observers_.end(), new_observer) == observers_.end()){
    //reached end, so observer is not in list
    observers_.push_back(new_observer);
  }else{
    std::cerr << "observer to add already exists" << std::endl;
  }
}

void Subject::RemoveObserver(Observer *observer_to_remove){

  auto found_obs = std::find(observers_.begin(), observers_.end(), observer_to_remove);
  if(found_obs != observers_.end()){
    //remove observer at iterator
    //This is an inefficient operation, due to having to copy all elements over if in middle
    //linked list for example would be more efficient, probably doesn't matter
    observers_.erase(found_obs);
  } else{
    std::cerr << "observer to remove doesn't exist" << std::endl;
  }

}

void Subject::Notify(){
  for(auto const obs : observers_){
    obs->onNotify();
  }
}
