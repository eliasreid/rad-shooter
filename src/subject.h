#ifndef SUBJECT_H
#define SUBJECT_H

#include <vector>
#include "observer.h"

class Subject
{
public:
  void AddObserver(Observer* new_observer);
  void RemoveObserver(Observer* observer_to_remove);
protected:
  void Notify();
private:
  std::vector<Observer *> observers_;

};

#endif // SUBJECT_H
