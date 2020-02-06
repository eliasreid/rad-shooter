#include <random>
#include <algorithm>
#include <iostream>
#include "enemyhandler.h"

EnemyHandler::EnemyHandler(SDL_Window* window, SDL_Renderer* renderer, Player* player) : spawn_period_(500), size_(30)
{
  window_ = window;
  player_ = player;
  renderer_ = renderer;

  prev_spawn_time_ = std::chrono::high_resolution_clock::now();
}

EnemyHandler::~EnemyHandler()
{
  for(auto &e : enemies_){
    e->Clean();
  }
}

void EnemyHandler::Init(){
  //start timer.
}

void EnemyHandler::Update(){

  std::vector<void*> to_remove; // save pointers to elements that should be removed.

  for(auto &e : enemies_){

    if(shot_){
      //check ray collision
      //      Physics::CollisionRayCircle()
      if(true){
//        to_remove.push_back(e);
      }
      shot_ = false;
    }

    //Check for out of bounds
    if(!e->isOnScreen()){
      e->Clean();
      e->setDead(true); //
//      to_remove.push_back(e);
      std::cout << "Killed enemy (off screen)" << std::endl; // working, I am setting them dead
    }

    //check for collision with player
    //      Physics::CollisionCircleCircle()
//    if(true){
//      player_->Damage();
//    }
  }

  //Is this working?


  enemies_.erase(
      std::remove_if(
          enemies_.begin(),
        enemies_.end(),
          [](Enemy* e) { return e->isDead(); }
          ),
        enemies_.end()
      );

  std::cout << "There is "<<enemies_.size() << " enemies being handled rn."<<std::endl;

  //second loop to delete the enemies with matching pointers.
  //TODO (memory leak without this.)

  //C++ has a remove if

  //Update enemies that still exist

  for(auto &e : enemies_){
    e->Update();
  }

  //if time since prev is larger than spawn_period_, then spawn an enemy
  if(is_spawning_){
    auto current_time = std::chrono::high_resolution_clock::now();
    auto time_since_prev_ = std::chrono::duration_cast<std::chrono::milliseconds>(current_time - prev_spawn_time_).count();

    if(time_since_prev_ > spawn_period_){
      SpawnEnemy(EnemyHandler::TOWARD_MIDDLE, 0.001);
      prev_spawn_time_ = current_time;
    }
  }

}

void EnemyHandler::Render(){
  for(auto &e : enemies_){
    e->Render();
  }

}


void EnemyHandler::SpawnEnemy(TYPE type, float speed){

  SDL_Rect spawn_rect;
  spawn_rect.w = size_;
  spawn_rect.h = size_;
  int screen_width, screen_height;
  SDL_GetWindowSize(window_, &screen_width, &screen_height);

  SIDE side = static_cast<SIDE>(rand() % 4);
  switch(side){
  case EnemyHandler::TOP:
    spawn_rect.x = rand() % screen_width;
    spawn_rect.y = -size_/2;
    break;
  case EnemyHandler::LEFT:
    spawn_rect.x = -size_/2;
    spawn_rect.y = rand() % screen_height;
    break;
  case EnemyHandler::RIGHT:
    spawn_rect.x = screen_width+size_/2;
    spawn_rect.y = rand() % screen_height;
    break;
  case EnemyHandler::BOTTOM:
    spawn_rect.x = rand() % screen_width;
    spawn_rect.y = screen_height+size_/2;
    break;
  }

  //based on location, initilize velocoty to travel toward middle of screen


  Physics::Vec2D vel = {0.0, 0.0};

  switch(type){
  case EnemyHandler::TOWARD_MIDDLE:
    //position of screen centre - position of enemy centre
    vel = Physics::Vec2D(screen_width / 2, screen_height / 2) - Physics::Centre(spawn_rect);
    Physics::Normalize(vel);
    break;
  default:
    break;
  }

  enemies_.push_back(new Enemy(renderer_, window_, "../rad-shooter-POC/assets/enemy.png", spawn_rect,vel*speed));
}

