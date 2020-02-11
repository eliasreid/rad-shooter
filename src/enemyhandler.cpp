#include <random>
#include <algorithm>
#include <iostream>
#include "enemyhandler.h"

EnemyHandler::EnemyHandler(SDL_Window* window, SDL_Renderer* renderer, Player* player) :
    spawn_period_(1000), size_(50), min_hit_period_(1000), is_spawning_(true), shot_(false)
{
  window_ = window;
  player_ = player;
  renderer_ = renderer;
}

EnemyHandler::~EnemyHandler()
{
  for(auto &e : enemies_){
    e->Clean();
  }
}

void EnemyHandler::Init(){
  spawn_timer_.Init(1000);
  damage_timer_.Init(1000); // This gives player 1 sec of invinsibilty at the start, and after gets hit
  SpawnEnemy(Enemy::TOWARD_MIDDLE, 0.1);
}

void EnemyHandler::PauseSw(){
  spawn_timer_.PauseSw();
  damage_timer_.PauseSw();
}

void EnemyHandler::HandleEvents(SDL_Event &e){
  if(e.type == SDL_MOUSEBUTTONDOWN){
    shot_ = true;
  }

  if(e.type == SDL_KEYDOWN){
    switch(e.key.keysym.sym){
    case SDLK_ESCAPE:
      PauseSw();
    }
  }
}

void EnemyHandler::Update(){

  for(auto &e : enemies_){
    e->Update();

    //Check for out of bounds
    if(!e->isOnScreen()){
      e->Clean();
      e->setDead(true);
    }

    if(!e->isDead() && shot_){
      Physics::Vec2D ray_start;
      Physics::Vec2D ray_end;
      player_->RayPoints(ray_start, ray_end);

      //check ray collision

      if(Physics::CollisionRayCircle(ray_start,ray_end, e->GetCircle())){
        e->setDead(true);
      }
    }

    // check for collision with player
    if(!e->isDead() && Physics::CollisionCircleCircle(player_->GetCircle(), e->GetCircle())){
      if(damage_timer_.CheckTimeout() == true){
        //TODO: set blinking for visual feedback of damage / invincibility
        player_->Damage();
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

  //if time since prev is larger than spawn_period_, then spawn an enemy
  if(is_spawning_){
    if(spawn_timer_.CheckTimeout()){
      SpawnEnemy(Enemy::TOWARD_MIDDLE, 0.1);
    }
  }

}

void EnemyHandler::Render(){
  for(auto &e : enemies_){
    e->Render();
  }
}

void EnemyHandler::SpawnEnemy(Enemy::TYPE enemy_type, float speed){

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
  switch(enemy_type){
  case Enemy::TOWARD_MIDDLE:
    //position of screen centre - position of enemy centre
    vel = Physics::Vec2D(screen_width / 2, screen_height / 2) - Physics::Centre(spawn_rect);
    Physics::Normalize(vel);
    break;
  case Enemy::TEST:
    spawn_rect.x = screen_width/2;
    spawn_rect.y = screen_height/2;
  default:
    break;
  }

  enemies_.push_back(new Enemy(enemy_type, renderer_, window_, "../rad-shooter-POC/assets/enemy.png", spawn_rect,vel*speed));
}

