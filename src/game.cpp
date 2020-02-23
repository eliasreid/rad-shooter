#include <iostream>
#include "game.h"
#include "physics.h"

Game::Game() : running_(false), paused_(false), game_over_(false) // false unless initialized
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
            player_ = std::make_shared<Player>(renderer_, "../rad-shooter/assets/player.png", player_init_rect, window_, 4);
            enemy_handler_ = std::make_shared<EnemyHandler>(window_, renderer_, player_);
            health_text_ = std::make_shared<HealthUI>(renderer_, window_, "Health: 4", TextBox::SCREEN_POS::TOP_LEFT, 40);
            game_over_text_ = std::make_shared<TextBox>(renderer_, window_, "Game Over", TextBox::SCREEN_POS::CENTRE, 65, false);
            //Score ui element doesn't update it's size dynamically, so the extra space are to give room for other digits.
            score_text_ = std::make_shared<ScoreUI>(renderer_, window_, "Score: 0          ", TextBox::SCREEN_POS::TOP_RIGHT, 40);
            //TODO tweak these to look good
            int reload_w = 100;
            int reload_h = 30;
            int reload_padding = 5;
            SDL_Rect reload_rect = { 0 + reload_padding,
                                    window_height - (reload_h + reload_padding),
                                   reload_w,
                                   reload_h};

            reload_ui_ = std::make_shared<ReloadUI>(renderer_, reload_rect);

            player_->AddObserver(health_text_);
            player_->AddObserver(shared_from_this());
            player_->AddObserver(enemy_handler_);
            player_->AddObserver(reload_ui_);

            enemy_handler_->Init();
            enemy_handler_->AddObserver(score_text_);
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
        paused_ = !paused_; //TODO send pause event to be handled by other classes? right now handling esc on object basis
        break;
      case SDLK_r:
        Restart();
        break;
      }
    }

    //Handle mouse input
    if(e.type == SDL_MOUSEBUTTONDOWN){
      if(game_over_){
        //Restart game
        game_over_ = false; // Better to do here or in Restart?
        Restart();
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
  score_text_->Render();
  game_over_text_->Render();
  reload_ui_->Render();
  SDL_RenderPresent(renderer_);
}

void Game::Restart(){

  player_->Reset();
  enemy_handler_->Reset();
  score_text_->Reset();
  game_over_text_->setVisible(false);
  //reset score (when exists)

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
  //most of these cleans should be taken care of with their destructors
  //not sure if explicit cleans here are necessary
  player_->Clean();
  game_over_text_->Clean();
  enemy_handler_->Clean();
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

void Game::onNotify(GameObject *obj, EVENT_TYPE event_type){
  //game object will be player
  switch(event_type){
  case EVENT_TYPE::PLAYER_DEAD:
    game_over_ = true;
    game_over_text_->setVisible(true);
    break;
  default:
    break;
  }

}
