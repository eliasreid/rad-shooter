#ifndef PLAYER_H
#define PLAYER_H

#include <SDL.h>
#include <math.h>
#include <chrono>
#include "gameobject.h"
#include "physics.h"
#include "subject.h"

class Player : public GameObject, public Subject
{
public:
  //Probably belongs elsewhere


  Player(SDL_Renderer* rend, std::string texture_path,  SDL_Rect initial_dest_rect, SDL_Window* window, int hp);

  void HandleEvents(SDL_Event& e);
  void Update() override;
  void Render() override;
  void Damage();
  Physics::Circle GetCircle();
  void RayPoints(Physics::Vec2D &vec1, Physics::Vec2D &vec2);
  int getHealth();

private:
  Physics::Circle circle_;
  float ray_velocity_;
  float ray_angle_ = 45 *M_PI/180; // angle in radians - zero is up, clockwise is positive
  float ray_length_;
  Physics::Vec2D ray_start_;
  Physics::Vec2D ray_end_;

  int health_remaining_;

  SDL_Window* window_;
};

#endif // PLAYER_H
