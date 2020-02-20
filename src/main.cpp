#include <iostream>
#include <memory>
#include <SDL.h>
#include "game.h"

int main(int argc, char* args[]){

  std::shared_ptr<Game> game = std::make_shared<Game>();

  if(!game->Init()){
    std::cerr << "Game failed to initialize" << std::endl;
  } else{

    while(game->IsRunning()){
      game->GameLoop();
    }

    game->Close();
  }
  return 0;
}
