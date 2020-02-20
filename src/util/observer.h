#ifndef OBSERVER_H
#define OBSERVER_H

#include "gameobject.h"
#include "event.h"

class Observer
{
public:
  //Assumes that the ptr we want to send is always a gameobject. often not going to need the ptr anyways
  virtual void onNotify(GameObject* obj, EVENT_TYPE event_type) = 0;
};

#endif // OBSERVER_H
