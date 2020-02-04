#ifndef ENEMY_H
#define ENEMY_H

#include "gameobject.h"
#include "physics.h"

class Enemy : public GameObject
{
public:
  Enemy(SDL_Renderer* rend, std::string texture_path,  SDL_Rect initial_dest_rect, Physics::Vec2D initial_velocity);

  void Update() override;
  //Doesn't need it's own Render function yet

private:
  Physics::Vec2D centre_;
  Physics::Vec2D velocity_;
};

#endif // ENEMY_H
