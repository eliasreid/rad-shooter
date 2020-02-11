#include <iostream>
#include "player.h"

Player::Player(SDL_Renderer* rend, std::string texture_path,  SDL_Rect initial_dest_rect, SDL_Window* window) :
  GameObject(rend, texture_path, initial_dest_rect) {

  window_ = window;
  int x_size, y_size;
  SDL_GetWindowSize(window_, &x_size, &y_size);
  ray_length_ = Physics::Length(x_size, y_size);
  circle_.rad = initial_dest_rect.w/2.0;

  ray_velocity_ = 0.0001; // will be an important gameplay parameter

  health_ = 2;

}

void Player::HandleEvents(SDL_Event &e){

  if(e.type == SDL_MOUSEMOTION){
    int x, y;
    SDL_GetMouseState(&x, &y);

    //player should be centered on mouse - used to update render rect in Update()
    circle_.ctr.x = x;
    circle_.ctr.y = y;
  }
}

void Player::Update(){

  if(health_ == 0){
    std::cout << "player's health has reached zero!" << std::endl;
    health_=-1;
  }

  //Update player's render destination rect
  dest_rect.x = circle_.ctr.x - dest_rect.w/2;
  dest_rect.y = circle_.ctr.y - dest_rect.h/2;

  //apply angular velocity to ray_angle.

  //vecolity is working fine for enemies, but ray isn't updating properly.

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
  //Basic rendering. Renders texture to screen at dest_rect
  GameObject::Render();

  //Additional rendering for player class

  //Render ray cursor
  SDL_SetRenderDrawColor(renderer_,0,0,0,255);
  SDL_RenderDrawLine(renderer_, ray_start_.x, ray_start_.y, ray_end_.x, ray_end_.y);
}

void Player::Damage(){
  std::cout << "player has been damaged!" << std::endl;
  health_--;
}

Physics::Circle Player::GetCircle(){
    return circle_;
}

void Player::RayPoints(Physics::Vec2D &vec1, Physics::Vec2D &vec2){
  vec1 = circle_.ctr;
  vec2 = ray_end_;
}
