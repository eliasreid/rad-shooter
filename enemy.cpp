#include "enemy.h"

Enemy::Enemy(SDL_Renderer* rend, SDL_Window* window, std::string texture_path,  SDL_Rect initial_dest_rect, Physics::Vec2D initial_velocity)
    : GameObject(rend, texture_path, initial_dest_rect), dead_(false){

  velocity_ = initial_velocity;
  window_ = window;
  circle_.ctr.x = initial_dest_rect.x + initial_dest_rect.w/2.0;
  circle_.ctr.y = initial_dest_rect.y + initial_dest_rect.h/2.0;
  circle_.rad = initial_dest_rect.w/2.0;


}

void Enemy::Update(){

  //calculate new centre point based physics
  Physics::Move(circle_.ctr, velocity_);

  //udpate render_rect
  dest_rect.x = circle_.ctr.x - dest_rect.w/2;
  dest_rect.y = circle_.ctr.y - dest_rect.h/2;

}

bool Enemy::isOnScreen(){
  int max_x, max_y;
  SDL_GetWindowSize(window_, &max_x, &max_y); // 1280, 720

  if(circle_.ctr.x > max_x + dest_rect.w){
    //OOB on right
    return false;
  }
  if(circle_.ctr.x < 0 - dest_rect.w){
    //OOB on right
    return false;
  }
  if(circle_.ctr.y > max_y + dest_rect.h){
    //OOB on right
    return false;
  }
  if(circle_.ctr.y < 0 - dest_rect.h){
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
  dead_ = dead;
}

Physics::Circle Enemy::GetCircle(){
    return circle_;
}
