#include "reloadui.h"
#include "player.h"
#include "physics.h"

ReloadUI::ReloadUI(SDL_Renderer* rend, SDL_Rect rect) : rend_(rend), outline_rect_(rect), is_filling_(false)
{
  int padding = 4;

  fill_rect_ = {outline_rect_.x +padding, outline_rect_.y + padding, outline_rect_.w -padding*2, outline_rect_.h -padding*2};
  max_fill_ = static_cast<double>(fill_rect_.w);
}

void ReloadUI::Update(){
  if(is_filling_){
    if(current_fill_ < max_fill_){
      current_fill_ += fill_rate_ * Physics::frametime_ms;
      fill_rect_.w = static_cast<int>(current_fill_);
    }else{
      //have reached filled rect
      is_filling_ = false;
      fill_rect_.w = static_cast<int>(max_fill_);
    }
  }
}

void ReloadUI::Render(){
  SDL_SetRenderDrawColor(rend_,0,0,0,255);
  SDL_RenderDrawRect(rend_, &outline_rect_);
  SDL_RenderFillRect(rend_, &fill_rect_);
}

void ReloadUI::Reset(){
  is_filling_ = false;
  fill_rect_.w = static_cast<int>(max_fill_);
}

void ReloadUI::onNotify(GameObject *obj, EVENT_TYPE event_type){
  auto player = dynamic_cast<Player*>(obj);
  switch(event_type){
  case EVENT_TYPE::PLAYER_SHOT:
    //Potential problem if player's reload time changes mid reload - animation won't be accurate.
    //This realistically shouldn't happen. If reload time changes, should probably manually reload anyway (send PLAYER_SHOT_READY)
    Refill(player->getReloadTime());
    break;
  case EVENT_TYPE::PLAYER_SHOT_READY:
    break;
  default:
    break;
  }
}

/**
 * @brief ReloadUI::Refill
 * Sets things up to start playing the "fill" animation
 */
void ReloadUI::Refill(int time_to_fill_ms){
  is_filling_ = true;
  current_fill_ = 0;
  fill_rect_.w = 0;
  fill_rate_ = max_fill_ / time_to_fill_ms;
}
