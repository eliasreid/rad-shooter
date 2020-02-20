#ifndef SUBJECT_H
#define SUBJECT_H

#include <vector>
#include <memory>
#include "observer.h"

class Subject
{
public:
  void AddObserver(std::shared_ptr<Observer> new_observer);
  void RemoveObserver(std::shared_ptr<Observer> observer_to_remove);
protected:
  void Notify(GameObject* obj, EVENT_TYPE event_type);
private:
  std::vector<std::shared_ptr<Observer>> observers_;

};

#endif // SUBJECT_H
