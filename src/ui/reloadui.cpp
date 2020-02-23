#include "reloadui.h"

ReloadUI::ReloadUI(SDL_Renderer* rend, SDL_Rect rect) : outline_rect_(rect), rend_(rend)
{
  //fill rect initialized to be slightly smaller rendered inside outline - 2 pixels should be good

  fill_rect_ = {outline_rect_.x +2, outline_rect_.y + 2, outline_rect_.w -4, outline_rect_.h -4};
  fill_amount_ = fill_rect_.w;
}

void ReloadUI::Render(){
  SDL_SetRenderDrawColor(rend_,0,0,0,255);
  SDL_RenderDrawRect(rend_, &outline_rect_);
  SDL_RenderFillRect(rend_, &fill_rect_);
}

void ReloadUI::onNotify(GameObject *obj, EVENT_TYPE event_type){

}

void ReloadUI::Refill(){

}
