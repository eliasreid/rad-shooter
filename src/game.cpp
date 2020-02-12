#include <iostream>
#include "game.h"
#include "physics.h"

Game::Game() : running_(false), paused_(false) // false unless initialized
{
}

Game::~Game(){

}

bool Game::Init(){
  bool success = true;

  //Init SDL subsystems
  if( SDL_Init( SDL_INIT_VIDEO ) < 0 ){
    std::cerr << "Unable to init SDL. Error: "<< SDL_GetError() << std::endl;
    success = false;
  } else{
    //SDL initialized

    //Set texture filtering to linear
    if( !SDL_SetHint( SDL_HINT_RENDER_SCALE_QUALITY, "1" ) )
    {
      std::cerr << "Warning: Linear texture filtering not enabled!" << std::endl;
    }

    //Create window
    //TODO: get the screen dimensions from config file? Eventually want to start game with a menu with options.
    const int window_width = 1280;
    const int window_height = 720;

    window_ = SDL_CreateWindow( "Rad Shooter", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, window_width, window_height, SDL_WINDOW_SHOWN );
    if( window_ == nullptr )
    {
      std::cerr<< "Window could not be created! SDL Error: "<< SDL_GetError() << std::endl;
      success = false;
    }
    else
    {
      //Create renderer for window
      renderer_ = SDL_CreateRenderer( window_, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC );
      if( renderer_ == nullptr )
      {
        std::cerr << "Renderer could not be created! SDL Error: " << SDL_GetError()<< std::endl;
        success = false;
      }
      else
      {
        //Initialize PNG loading
        int imgFlags = IMG_INIT_PNG;
        if( !( IMG_Init( imgFlags ) & imgFlags ) )
        {
          std::cerr<<"SDL_image could not initialize! SDL_image Error: " << IMG_GetError()<<std::endl;
          success = false;
        } else{

          if(TTF_Init() == -1){
            std::cerr<<"SDL_ttf could not initialize! SDL_ttf Error: " << TTF_GetError()<<std::endl;
            success = false;
          }else{

            //Create player with initial size / position.
            const int player_x_size = 30;
            const int player_y_size = 30;

            SDL_Rect player_init_rect = {window_width / 2  -  player_x_size / 2,
                                          window_height / 2 - player_y_size / 2,
                                         player_x_size,
                                         player_y_size};

            //Instantiate physics and player
            physics_ = Physics();
            player_ = new Player(renderer_, "../rad-shooter-POC/assets/player.png", player_init_rect, window_);
            enemy_handler_ = new EnemyHandler(window_, renderer_, player_);
            health_text_ = new TextBox(renderer_,"Health: 2", 0, 0);


            enemy_handler_->Init();
  //          paused_=true;

            //Hide mouses - leave mouse on for development
  //          SDL_ShowCursor(SDL_DISABLE);
          }
        }
      }
    }
  }
  running_ = true;
  return success;

}

void Game::HandleEvents(){

  //SDL_PollEvents will return zero when there's no events left on the queue
  while(SDL_PollEvent(&e) != 0){

    //Handle game related Keyboard inputs.
    if(e.type == SDL_KEYDOWN){
      switch(e.key.keysym.sym){
      case SDLK_ESCAPE:
        paused_ = !paused_;
      }
    }

    if(e.type == SDL_QUIT){
      running_ = false;
    } else{
      player_->HandleEvents(e);
      enemy_handler_->HandleEvents(e);
    }
  }
}

void Game::Update(){
  player_->Update();
  enemy_handler_->Update();

}

void Game::Render(){
  SDL_SetRenderDrawColor(renderer_, 0xFF, 0xFF, 0xFF, 0xFF);
  SDL_RenderClear(renderer_);
  player_->Render();
  enemy_handler_->Render();
  health_text_->Render();
  SDL_RenderPresent(renderer_);
}

void Game::GameLoop(){
  HandleEvents();
  if(!paused_){
    Update();
  }
  physics_.UpdateTime();
  Render();
}

void Game::Close(){
  player_->Clean();
  health_text_->Clean();
//  enemy_handler_->Clean(); //TODO: need to implement this
  SDL_DestroyRenderer(renderer_);
  renderer_ = nullptr;
  SDL_DestroyWindow(window_);
  window_ = nullptr;

  TTF_Quit();
  IMG_Quit();
  SDL_Quit();
}

bool Game::IsRunning(){
  return running_;
}
