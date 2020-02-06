#include "enemy.h"

Enemy::Enemy(SDL_Renderer* rend, SDL_Window* window, std::string texture_path,  SDL_Rect initial_dest_rect, Physics::Vec2D initial_velocity)
    : GameObject(rend, texture_path, initial_dest_rect), dead_(false){

  velocity_ = initial_velocity;
  window_ = window;
  centre_.x = initial_dest_rect.x + initial_dest_rect.w/2;
  centre_.y = initial_dest_rect.y + initial_dest_rect.h/2;


}

void Enemy::Update(){

  //calculate new centre point based physics
  Physics::Move(centre_, velocity_);

  //udpate render_rect
  dest_rect.x = centre_.x - dest_rect.w/2;
  dest_rect.y = centre_.y - dest_rect.h/2;

}

bool Enemy::isOnScreen(){
  int max_x, max_y;
  SDL_GetWindowSize(window_, &max_x, &max_y);

  if(centre_.x > max_x + dest_rect.w){
    //OOB on right
    return false;
  }
  if(centre_.x > max_x + dest_rect.w){
    //OOB on right
    return false;
  }
  if(centre_.x > max_x + dest_rect.w){
    //OOB on right
    return false;
  }
  if(centre_.x > max_x + dest_rect.w){
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
