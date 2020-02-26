#ifndef PARTICLE_H
#define PARTICLE_H

#include <SDL.h>
#include "gameobject.h"
#include "physics.h"

class Particle : public GameObject
{
public:
  Particle(SDL_Renderer* rend, SDL_Texture* preloaded_texture, SDL_Rect initial_dest_rect, int lifetime, float speed);

  void Update() override;

private:
  float fade_rate_;
  float lifetime_;
  float current_alpha_;
  Physics::Circle circle_;
  Physics::Vec2D velocity_;
  bool is_deletable_;
};

#endif // PARTICLE_H
