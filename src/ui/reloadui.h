#ifndef RELOADUI_H
#define RELOADUI_H

#include <SDL.h>
#include "observer.h"

class ReloadUI : public Observer
{
public:
  ReloadUI(SDL_Renderer* rend, SDL_Rect rect);

  void Update();
  void Render();
  void Reset();

private:

  SDL_Renderer* rend_;
  SDL_Rect outline_rect_;
  SDL_Rect fill_rect_; // stays constant, then just render a rect in here based ond fill amount
  double max_fill_;
  double current_fill_;
  double fill_rate_;

  bool is_filling_;

  void onNotify(GameObject *obj, EVENT_TYPE event_type) override;
  void Refill(int time_to_fill_ms);

};

#endif // RELOADUI_H
