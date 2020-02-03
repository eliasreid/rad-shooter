#ifndef GAME_H
#define GAME_H
#include <SDL.h>
#include <SDL_image.h>
#include "gameobject.h"
#include "player.h"

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
  SDL_Renderer* renderer_;
  SDL_Window* window_;
  SDL_Event e;

  Player* player_;
};

#endif // GAME_H
