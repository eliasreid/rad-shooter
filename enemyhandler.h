#ifndef ENEMYHANDLER_H
#define ENEMYHANDLER_H

#include <vector>
#include <chrono>

#include "enemy.h"
#include "physics.h"
#include "player.h"

class EnemyHandler
{
public:
  EnemyHandler(SDL_Window* window, SDL_Renderer* renderer, Player* player);
  ~EnemyHandler();

  enum TYPE{ // TODO: should belong to Enemy, not EnemyHandler
    TOWARD_MIDDLE = 0,
    TRACKING,
    ZIGZAG
  };

  void PlayerShot();
  void Init();
  void Update();
  void Render();
  void SpawnEnemy(TYPE type, float speed);

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
  int size_;
  bool shot_;
  SDL_Window* window_;
  Player* player_;
  SDL_Renderer* renderer_;

  std::chrono::high_resolution_clock::time_point  prev_spawn_time_;

};

#endif // ENEMYHANDLER_H
