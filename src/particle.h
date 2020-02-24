#ifndef PARTICLE_H
#define PARTICLE_H

#include <SDL.h>
#include "gameobject.h"
#include "physics.h"

class Particle : public GameObject
{
public:
  Particle(SDL_Renderer* rend, SDL_Rect initial_dest_rect, int lifetime, float speed);

  void Update() override;

private:
  int lifetime_;
  float fade_rate;
  int current_alpha_;
  Physics::Circle circle_;
  Physics::Vec2D velocity_;
};

#endif // PARTICLE_H
