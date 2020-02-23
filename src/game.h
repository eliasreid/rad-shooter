#ifndef GAME_H
#define GAME_H
#include <vector>
#include <memory>
#include <SDL.h>
#include <SDL_image.h>
#include "gameobject.h"
#include "player.h"
#include "enemy.h"
#include "enemyhandler.h"
#include "observer.h"
#include "textbox.h"
#include "healthui.h"
#include "scoreui.h"
#include "reloadui.h"

class Game : public Observer, public std::enable_shared_from_this<Game>
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
  std::shared_ptr<Player> player_;
  std::shared_ptr<EnemyHandler> enemy_handler_;
  std::shared_ptr<HealthUI> health_text_;
  std::shared_ptr<TextBox> game_over_text_;
  std::shared_ptr<ScoreUI> score_text_;
  std::shared_ptr<ReloadUI> reload_ui_;

  void onNotify(GameObject *obj, EVENT_TYPE event_type) override;

};

#endif // GAME_H
