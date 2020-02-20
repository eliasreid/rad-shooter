#ifndef GAME_H
#define GAME_H
#include <vector>
#include <SDL.h>
#include <SDL_image.h>
#include "gameobject.h"
#include "player.h"
#include "enemy.h"
#include "enemyhandler.h"
#include "observer.h"
#include "textbox.h"
#include "healthui.h"

class Game : public Observer
{
public:
  Game();
  ~Game();

  bool Init();

  void GameLoop();
  void HandleEvents();
  void Update();
  void Render();
  void Restart();
  void Close();

  bool IsRunning();

private:

  bool running_;
  bool paused_;
  bool game_over_;
  SDL_Renderer* renderer_;
  SDL_Window* window_;
  SDL_Event e;

  Physics physics_;
  Player* player_;
  EnemyHandler* enemy_handler_;
  HealthUI* health_text_;
  TextBox* game_over_text_;

  void onNotify(GameObject *obj, EVENT_TYPE event_type) override;

};

#endif // GAME_H
