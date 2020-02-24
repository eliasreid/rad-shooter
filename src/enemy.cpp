#include "enemy.h"

Enemy::Enemy(TYPE enemy_type, SDL_Renderer* rend, SDL_Window* window, std::string texture_path,  SDL_Rect initial_dest_rect, Physics::Vec2D initial_velocity)
    : GameObject(rend, texture_path, initial_dest_rect), dead_(false){

  velocity_ = initial_velocity;
  window_ = window;
  type_ = enemy_type;
  circle_.ctr.x = initial_dest_rect.x + initial_dest_rect.w/2.0;
  circle_.ctr.y = initial_dest_rect.y + initial_dest_rect.h/2.0;
  circle_.rad = initial_dest_rect.w/2.0;

}

void Enemy::Update(){

  Physics::Move(circle_.ctr, velocity_);

  //udpate render_rect
  dest_rect_.x = circle_.ctr.x - dest_rect_.w/2;
  dest_rect_.y = circle_.ctr.y - dest_rect_.h/2;

}

bool Enemy::isOnScreen(){
  int max_x, max_y;
  SDL_GetWindowSize(window_, &max_x, &max_y); // 1280, 720

  if(circle_.ctr.x > max_x + dest_rect_.w){
    //OOB on right
    return false;
  }
  if(circle_.ctr.x < 0 - dest_rect_.w){
    //OOB on right
    return false;
  }
  if(circle_.ctr.y > max_y + dest_rect_.h){
    //OOB on right
    return false;
  }
  if(circle_.ctr.y < 0 - dest_rect_.h){
    //OOB on right
    return false;
  }

  return true;
}

bool Enemy::isDead(){
  return dead_;
}
 //Doesn't acutally need its own functino for this - could set dead in Clean
void Enemy::setDead(bool dead){
  if(type_ != TEST){
    dead_ = dead;
  }
}

Physics::Circle Enemy::getCircle(){
    return circle_;
}
