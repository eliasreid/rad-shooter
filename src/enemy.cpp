#include <iostream>
#include "enemy.h"

Enemy::Enemy(TYPE enemy_type, SDL_Renderer* rend, SDL_Window* window, std::string texture_path,  SDL_Rect initial_dest_rect, Physics::Vec2D initial_velocity)
    : GameObject(rend, texture_path, initial_dest_rect), is_dead_(false), is_exploding_(false), is_deletable_(false){

  velocity_ = initial_velocity;
  window_ = window;
  type_ = enemy_type;
  circle_.ctr.x = initial_dest_rect.x + initial_dest_rect.w/2.0;
  circle_.ctr.y = initial_dest_rect.y + initial_dest_rect.h/2.0;
  circle_.rad = initial_dest_rect.w/2.0;

  particles_.reserve(NUM_PARTICLES);
  explode_timer_.Init(PARTICLE_LIFETIME);
  explode_timer_.setActive(false);
}

void Enemy::Update(){

  if(!is_exploding_){
    Move();
  }else{
    //May want to still move while exploding (could put move() outside of if else)
    if(!explode_timer_.CheckTimeout()){
      std::cout << "Update particles" << std::endl;
      UpdateParticles();
    } else {
      std::cout << "Stop updating particles, set enemy to be deleted" << std::endl;
      //Timer timed out, time to go
      is_exploding_ = false;
      is_deletable_ = true;
    }
  }

}
void Enemy::UpdateParticles(){

  for(auto &particle : particles_){
    particle->Update();
  }

}
/**
 * @brief Enemy::Move Moves circle position and updates render rect accordingly
 */
void Enemy::Move(){
  Physics::Move(circle_.ctr, velocity_);

  //udpate render_rect
  dest_rect_.x = circle_.ctr.x - dest_rect_.w/2;
  dest_rect_.y = circle_.ctr.y - dest_rect_.h/2;
}

void Enemy::Render(){
  //TEMP: just going to stop rendering the enemy while exploding
  if(!is_exploding_){
    GameObject::Render();
  }else{
    for(auto &particle : particles_){
      particle->Render();
    }
  }
}

bool Enemy::isOnScreen(){
  int max_x, max_y;
  SDL_GetWindowSize(window_, &max_x, &max_y); // 1280, 720

  //Check screen bounds
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
  return is_dead_;
}
bool Enemy::isDeletable(){
  return is_deletable_;
}
void Enemy::setDeletable(bool deletable){
  is_deletable_ = deletable;
  if(is_deletable_=true)
    is_dead_ = true;// Set dead as well so that we avoiding other checks in enemyhandler

}

void Enemy::Shot(){
  is_dead_ = true;
  is_exploding_ = true;

  for(int i =0; i<NUM_PARTICLES; i++){
    SDL_Rect p_rect = dest_rect_;
    p_rect.w=5; p_rect.h=5;
    particles_.emplace_back(std::make_unique<Particle>(renderer_, p_rect, PARTICLE_LIFETIME, 0.5));
  }
  explode_timer_.setActive(true);
}

Physics::Circle Enemy::getCircle(){
    return circle_;
}

void Enemy::PauseSw(){
  explode_timer_.PauseSw();
}
