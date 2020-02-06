#ifndef PLAYER_H
#define PLAYER_H

#include <SDL.h>
#include <math.h>
#include <chrono>
#include "gameobject.h"
#include "physics.h"

class Player : public GameObject
{
public:
  //Probably belongs elsewhere


  Player(SDL_Renderer* rend, std::string texture_path,  SDL_Rect initial_dest_rect, SDL_Window* window);

  void HandleEvents(SDL_Event& e);
  void Update() override;
  void Render() override;
  void Damage();

private:
  Physics::Vec2D centre_;
  float ray_velocity_;
  float ray_angle_ = 45 *M_PI/180; // angle in radians - zero is up, clockwise is positive
  float ray_length_;
  Physics::Vec2D ray_start_;
  Physics::Vec2D ray_end_;

  int health_;

  SDL_Window* window_;
};

#endif // PLAYER_H
