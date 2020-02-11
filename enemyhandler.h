#ifndef ENEMYHANDLER_H
#define ENEMYHANDLER_H

#include <vector>
#include <chrono>

#include "enemy.h"
#include "physics.h"
#include "player.h"
#include "timer.h"

class EnemyHandler
{
public:
  EnemyHandler(SDL_Window* window, SDL_Renderer* renderer, Player* player);
  ~EnemyHandler();

  void Init();
  void HandleEvents(SDL_Event& e);
  void Update();
  void Render();
  void PauseSw();
  void SpawnEnemy(Enemy::TYPE type, float speed);

private:

  enum SIDE{
    TOP = 0,
    LEFT,
    RIGHT,
    BOTTOM
  };

  std::vector<Enemy*> enemies_;
  bool is_spawning_;
  unsigned int spawn_period_;
  unsigned int min_hit_period_;
  int size_;
  bool shot_;
  Timer spawn_timer_;
  Timer damage_timer_;
  SDL_Window* window_;
  Player* player_;
  SDL_Renderer* renderer_;

  std::chrono::high_resolution_clock::time_point  prev_spawn_time_;
  std::chrono::high_resolution_clock::time_point  prev_hit_time_;

};

#endif // ENEMYHANDLER_H
