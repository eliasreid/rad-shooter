#ifndef GAME_H
#define GAME_H
#include <SDL.h>
#include <SDL_image.h>
#include <vector>
#include "gameobject.h"
#include "player.h"
#include "enemy.h"
#include "enemyhandler.h"

class Game
{
public:
  Game();
  ~Game();

  bool Init();

  void GameLoop();
  void HandleEvents();
  void Update();
  void Render();
  void Close();

  bool IsRunning();

private:

  bool running_;
  bool paused_;
  SDL_Renderer* renderer_;
  SDL_Window* window_;
  SDL_Event e;

  Physics physics_;
  Player* player_;
  EnemyHandler* enemy_handler_;
//  std::vector<Enemy*> enemies_;

  void SpawnEnemy();

};

#endif // GAME_H
