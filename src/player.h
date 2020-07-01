#ifndef PLAYER_H
#define PLAYER_H

#include <SDL.h>
#include <math.h>
#include <chrono>
#include <utility>
#include "gameobject.h"
#include "physics.h"
#include "subject.h"
#include "timer.h"

class Player : public GameObject, public Subject
{
public:
  //Probably belongs elsewhere
  Player(SDL_Renderer* rend, std::string texture_path,  SDL_Rect initial_dest_rect, SDL_Window* window, int hp);

  void HandleEvents(SDL_Event& e);
  void Update() override;
  void Render() override;
  void Reset();
  void RenderLine();
  void Damage(bool is_collision = true);
  Physics::Circle getCircle();
  std::pair<Physics::Vec2, Physics::Vec2> getLinePoints() const;
  int getHealth();
  int getReloadTime();
  bool isInvincible()const;

private:
  Physics::Circle circle_;
  float ray_velocity_;
  float ray_angle_; // angle in radians - zero is up, clockwise is positive
  float ray_length_;
  Physics::Vec2 ray_start_;
  Physics::Vec2 ray_end_;
  Timer invincibility_timer_;
  Timer blink_timer_;
  Timer reload_timer_;
  bool is_invincible_;
  bool is_visible_;
  bool shot_ready_;
  int health_remaining_;
  int max_hp_;
  int reload_time_;

  SDL_Window* window_;

  void setHealth(int health);
  void ReloadShot();
  void Shoot();
  void MoveToMouse();
};

#endif // PLAYER_H
