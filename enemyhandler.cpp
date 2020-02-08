#include <random>
#include <algorithm>
#include <iostream>
#include "enemyhandler.h"

EnemyHandler::EnemyHandler(SDL_Window* window, SDL_Renderer* renderer, Player* player) :
    spawn_period_(3000), size_(30), min_hit_period_(1000)
{
  window_ = window;
  player_ = player;
  renderer_ = renderer;

  prev_spawn_time_ = std::chrono::high_resolution_clock::now();
  prev_hit_time_ = std::chrono::high_resolution_clock::now(); // doing this means he player can't be hit until min_hit_period_ has elapsed
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

void EnemyHandler::HandleEvents(SDL_Event &e){
  if(e.type == SDL_MOUSEBUTTONDOWN){
    shot_ = true;
  }
}

void EnemyHandler::Update(){

  std::vector<void*> to_remove; // save pointers to elements that should be removed.

  for(auto &e : enemies_){

    if(shot_){
      Physics::Vec2D ray_start;
      Physics::Vec2D ray_end;
      player_->RayPoints(ray_start, ray_end);

      //check ray collision

      if(Physics::CollisionRayCircle(ray_start,ray_end, e->GetCircle())){
        e->setDead(true);
      }
    }

    //Check for out of bounds
    if(!e->isOnScreen()){
      e->Clean();
      e->setDead(true);
    }

//    check for collision with player
    if(Physics::CollisionCircleCircle(player_->GetCircle(), e->GetCircle())){
      auto current_time = std::chrono::high_resolution_clock::now();
      auto time_since_prev = std::chrono::duration_cast<std::chrono::milliseconds>(current_time-prev_hit_time_).count();

      if(time_since_prev > min_hit_period_){
        player_->Damage();
        prev_hit_time_ = current_time;
      }

    }
  }
  shot_ = false;

  enemies_.erase(
      std::remove_if(
          enemies_.begin(),
        enemies_.end(),
          [](Enemy* e) { return e->isDead(); }
          ),
        enemies_.end()
      );

  for(auto &e : enemies_){
    e->Update();
  }

  //if time since prev is larger than spawn_period_, then spawn an enemy
  if(is_spawning_){
    auto current_time = std::chrono::high_resolution_clock::now();
    auto time_since_prev = std::chrono::duration_cast<std::chrono::milliseconds>(current_time - prev_spawn_time_).count();

    if(time_since_prev > spawn_period_){
      SpawnEnemy(EnemyHandler::TOWARD_MIDDLE, 0.1);
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

