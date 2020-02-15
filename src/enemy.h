#ifndef ENEMY_H
#define ENEMY_H

#include "gameobject.h"
#include "physics.h"

class Enemy : public GameObject
{
public:
  enum TYPE{
    TOWARD_MIDDLE = 0,
    TEST,
    TRACKING,
    ZIGZAG
  };

  Enemy(TYPE enemy_type, SDL_Renderer* rend, SDL_Window* window, std::string texture_path,  SDL_Rect initial_dest_rect, Physics::Vec2D initial_velocity);

  void Update() override;
  bool isOnScreen();
  bool isDead();
  void setDead(bool dead);
  Physics::Circle getCircle();
  //Doesn't need it's own Render function yet

private:
  Physics::Circle circle_;
  Physics::Vec2D velocity_;
  SDL_Window* window_;
  bool dead_;
  TYPE type_;
};

#endif // ENEMY_H
