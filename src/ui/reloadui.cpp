#include "reloadui.h"

ReloadUI::ReloadUI(SDL_Renderer* rend, SDL_Rect rect) : outline_rect_(rect), rend_(rend)
{
  int padding = 4;

  fill_rect_ = {outline_rect_.x +padding, outline_rect_.y + padding, outline_rect_.w -padding*2, outline_rect_.h -padding*2};
  max_fill_ = fill_rect_.w;
}

void ReloadUI::Render(){
  SDL_SetRenderDrawColor(rend_,0,0,0,255);
  SDL_RenderDrawRect(rend_, &outline_rect_);
  SDL_RenderFillRect(rend_, &fill_rect_);
}

void ReloadUI::onNotify(GameObject *obj, EVENT_TYPE event_type){
  switch(event_type){
  case EVENT_TYPE::PLAYER_SHOT:
    //empty fill rect

    //Ideally can Refill function initiated a fill animation
    Refill();
    break;
  case EVENT_TYPE::PLAYER_SHOT_READY:
    //Shouldn't need this case
    fill_rect_.w = max_fill_;
    break;
  default:
    break;
  }
}

void ReloadUI::Refill(){
  fill_rect_.w = 0;

  //start dynamically increasing fill_amount somehow?
}
