#ifndef ENEMYHANDLER_H
#define ENEMYHANDLER_H

#include <vector>
#include <chrono>
#include <memory>
#include "enemy.h"
#include "physics.h"
#include "player.h"
#include "timer.h"
#include "event.h"

static const size_t MAX_ENEMIES = 100;
static const double ENEMY_SPEED = 0.2;

class EnemyHandler : public Observer, public Subject
{
public:
  EnemyHandler(SDL_Window* window, SDL_Renderer* renderer, std::shared_ptr<Player> player);
  ~EnemyHandler();

  void Init();
  void HandleEvents(SDL_Event& e);
  void Update();
  void Render();
  void Reset();
  void Clean();
  void PauseSw();
  void SpawnEnemy(Enemy::TYPE type, float speed);

private:

  enum SIDE{
    TOP = 0,
    LEFT,
    RIGHT,
    BOTTOM
  };

  std::vector<std::shared_ptr<Enemy>> enemies_;
  bool is_spawning_;
  unsigned int spawn_period_;
  unsigned int min_hit_period_;
  int size_;
  bool player_shot_;
  Timer spawn_timer_;
  SDL_Window* window_;
  std::shared_ptr<Player> player_;
  SDL_Renderer* renderer_;

  std::chrono::high_resolution_clock::time_point  prev_spawn_time_;
  std::chrono::high_resolution_clock::time_point  prev_hit_time_;

  void onNotify(GameObject *obj, EVENT_TYPE event_type) override;

};

#endif // ENEMYHANDLER_H
