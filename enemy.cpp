#include "enemy.h"

Enemy::Enemy(SDL_Renderer* rend, std::string texture_path,  SDL_Rect initial_dest_rect, Physics::Vec2D initial_velocity)
  : GameObject(rend, texture_path, initial_dest_rect){

  velocity_ = initial_velocity;
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
