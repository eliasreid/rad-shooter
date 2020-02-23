#ifndef RELOADUI_H
#define RELOADUI_H

#include <SDL.h>
#include "observer.h"

class ReloadUI : public Observer
{
public:
  ReloadUI(SDL_Renderer* rend, SDL_Rect rect);

  void Render();

private:

  int fill_amount_; // ranges from 0 to width of fill_rect_
  SDL_Rect outline_rect_;
  SDL_Rect fill_rect_; // stays constant, then just render a rect in here based ond fill amount
  SDL_Renderer* rend_;

  void onNotify(GameObject *obj, EVENT_TYPE event_type) override;
  void Refill();

};

#endif // RELOADUI_H
