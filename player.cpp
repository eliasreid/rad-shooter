#include <iostream>
#include "player.h"

Player::Player(SDL_Renderer* rend, std::string texture_path,  SDL_Rect initial_dest_rect, SDL_Window* window) :
  GameObject(rend, texture_path, initial_dest_rect) {

  window_ = window;
  int x_size, y_size;
  SDL_GetWindowSize(window_, &x_size, &y_size);
  ray_length_ = Physics::Length(x_size, y_size);

  ray_velocity_ = 0.001; // will be an important gameplay parameter

  health_ = 2;

}

void Player::HandleEvents(SDL_Event &e){

  if(e.type == SDL_MOUSEMOTION){
    int x, y;
    SDL_GetMouseState(&x, &y);

    //player should be centered on mouse - used to update render rect in Update()
    centre_.x = x;
    centre_.y = y;

  }
}

void Player::Update(){

  if(health_ < 1){
    std::cout << "player's health has reached zero!" << std::endl;
  }

  //Update player's render destination rect
  dest_rect.x = centre_.x - dest_rect.w/2;
  dest_rect.y = centre_.y - dest_rect.h/2;

  //apply angular velocity to ray_angle.
  Physics::Move(ray_angle_, ray_velocity_);
  if(ray_angle_ > 360.0){
    ray_angle_ -= 360.0;
  }

  //Set ray start/endpoint based on new angle.
  ray_start_ = centre_;
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

