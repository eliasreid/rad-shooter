#include <random>
#include "particle.h"
#include <iostream>


Particle::Particle(SDL_Renderer* rend, SDL_Rect initial_dest_rect, int lifetime, float speed) :
  GameObject(rend, "../rad-shooter/assets/particle.png", initial_dest_rect), lifetime_(lifetime), current_alpha_(255)
{
  fade_rate_ = static_cast<float>(current_alpha_) / static_cast<float>(lifetime_);

  //Initialize circle
  circle_.ctr.x = initial_dest_rect.x + initial_dest_rect.w/2.0;
  circle_.ctr.y = initial_dest_rect.y + initial_dest_rect.h/2.0;
  circle_.rad = initial_dest_rect.w/2.0;

  //Initialize velocity to random direction - Could optimize by pre-calculating random vectors and storing in Physics class
  float random_angle_rad = rand() % 360 * M_PI/180.0;
  velocity_.x = std::sin(random_angle_rad);
  velocity_.y = std::cos(random_angle_rad);

  velocity_ = velocity_ * speed;
}

void Particle::Update(){

  Physics::Move(circle_.ctr, velocity_);

  //udpate render_rect
  dest_rect_.x = circle_.ctr.x - dest_rect_.w/2;
  dest_rect_.y = circle_.ctr.y - dest_rect_.h/2;

  //fade alpha value and update for rendering
  current_alpha_ = current_alpha_ - fade_rate_ * Physics::frametime_ms;
  SDL_SetTextureAlphaMod(texture_, current_alpha_);
}
