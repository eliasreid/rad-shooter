#include <iostream>
#include "player.h"
#include "event.h"

Player::Player(SDL_Renderer* rend, std::string texture_path,  SDL_Rect initial_dest_rect, SDL_Window* window, int hp) :
  GameObject(rend, texture_path, initial_dest_rect), is_invincible(false), is_visible_(true) {

  window_ = window;
  int x_size, y_size;
  SDL_GetWindowSize(window_, &x_size, &y_size);
  ray_length_ = Physics::Length(x_size, y_size);
  circle_.rad = initial_dest_rect.w/2.0;

  ray_velocity_ = 0.0001; // will be an important gameplay parameter

  health_remaining_ = hp;

  invincibility_timer_.Init(1000, true);
  blink_timer_.Init(80);
}

void Player::HandleEvents(SDL_Event &e){

  switch(e.type){
  case SDL_MOUSEMOTION:{
    int x, y;
    SDL_GetMouseState(&x, &y);
    //player should be centered on mouse - used to update render rect in Update()
    circle_.ctr.x = x;
    circle_.ctr.y = y;
  } break;

  case SDL_MOUSEBUTTONDOWN:
    Notify(this, EVENT_TYPE::PLAYER_SHOT);
    break;
  case SDL_KEYDOWN:
    switch(e.key.keysym.sym){
      case SDLK_ESCAPE:
        invincibility_timer_.PauseSw();
    }
  default:
    break;
  }

  if(e.type == SDL_MOUSEMOTION){
    int x, y;
    SDL_GetMouseState(&x, &y);

    //player should be centered on mouse - used to update render rect in Update()
    circle_.ctr.x = x;
    circle_.ctr.y = y;
  }
}

void Player::Update(){
  //Update player's render destination rect
  dest_rect.x = circle_.ctr.x - dest_rect.w/2;
  dest_rect.y = circle_.ctr.y - dest_rect.h/2;

  //apply angular velocity to ray_angle.
  Physics::Move(ray_angle_, ray_velocity_);
  if(ray_angle_ > 360.0){
    ray_angle_ -= 360.0;
  }

  //Set ray start/endpoint based on new angle.
  ray_start_ = circle_.ctr;
  ray_end_.x = ray_start_.x + ray_length_ * sin(ray_angle_);
  ray_end_.y = ray_start_.y - ray_length_ * cos(ray_angle_);
}

void Player::Render(){

  //If player is invincible, need additional checks and a timer to blink every X time interval
  if(is_invincible){
    // keep checking until returns true, then reset invinsibility timer - start timed out
    if(!invincibility_timer_.CheckTimeout()){
      if(blink_timer_.CheckTimeout()){
        is_visible_ = !is_visible_;
      }
      if(is_visible_){
        GameObject::Render();
        RenderLine();
      }
    } else{
      is_invincible = false;
      is_visible_ = true;
      invincibility_timer_.Reset(true);
    }
  } else{
    //render normally
    GameObject::Render();
    RenderLine();
  }
}
void Player::RenderLine(){
  SDL_SetRenderDrawColor(renderer_,0,0,0,255);
  SDL_RenderDrawLine(renderer_, ray_start_.x, ray_start_.y, ray_end_.x, ray_end_.y);
}

void Player::Damage(){
  if(invincibility_timer_.CheckTimeout()){
    is_invincible = true;
    if(health_remaining_ > 0){
      health_remaining_--;
      Notify(this, EVENT_TYPE::PLAYER_DAMAGED);
      std::cout << "player has been damaged! health_ is now  " << health_remaining_ << std::endl;
    }else{
      std::cout << "Overkill!" << std::endl;
    }
  }
}

Physics::Circle Player::getCircle(){
    return circle_;
}

void Player::RayPoints(Physics::Vec2D &vec1, Physics::Vec2D &vec2){
  vec1 = circle_.ctr;
  vec2 = ray_end_;
}

int Player::getHealth(){
  return health_remaining_;
}
