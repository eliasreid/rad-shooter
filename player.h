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


  Player(SDL_Renderer* rend, std::string texture_path,  SDL_Rect intial_dest_rect, SDL_Window* window);

  void HandleEvents(SDL_Event& e);
  void Update() override;
  void Render() override;

private:
  Physics::Vec2D player_centre;
  float ray_velocity;
  float ray_angle = 45 *M_PI/180; // angle in radians - zero is up, clockwise is positive
  float ray_length;
  Physics::Vec2D ray_start;
  Physics::Vec2D ray_end;

  std::chrono::high_resolution_clock::time_point prev_time;
  SDL_Window* window_;
};

#endif // PLAYER_H
