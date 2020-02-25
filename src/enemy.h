#ifndef ENEMY_H
#define ENEMY_H

#include <vector>
#include <memory>
#include "gameobject.h"
#include "physics.h"
#include "particle.h"
#include "timer.h"

static const int NUM_PARTICLES = 10;
static const int PARTICLE_LIFETIME = 1000;

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
  void UpdateParticles();
  void Render() override;
  void PauseSw();
  bool isOnScreen();
  bool isDead();
  bool isDeletable();
  void setDeletable(bool deletable = true);
  void Shot();
  Physics::Circle getCircle();

private:
  Physics::Circle circle_;
  Physics::Vec2D velocity_;
  SDL_Window* window_;
  bool is_dead_;
  bool is_exploding_;
  bool is_deletable_;
  TYPE type_;
  Timer explode_timer_;
  std::vector<std::unique_ptr<Particle>> particles_;

  void Move();
};

#endif // ENEMY_H
