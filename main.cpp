#include <iostream>
#include <SDL.h>
#include "game.h"

int main(int argc, char* args[]){

  Game game;

  if(!game.Init()){
    std::cerr << "Game failed to initialize" << std::endl;
  } else{

    while(game.IsRunning()){
      game.GameLoop();
    }

    game.Close();
  }
  return 0;
}
