#include <random>
#include <algorithm>
#include <iostream>
#include "enemyhandler.h"

EnemyHandler::EnemyHandler(SDL_Window* window, SDL_Renderer* renderer, Player* player) :
    spawn_period_(1000), size_(50), min_hit_period_(1000), is_spawning_(true), player_shot_(false)
{
  window_ = window;
  player_ = player;
  renderer_ = renderer;
  enemies_.reserve(MAX_ENEMIES);

}

EnemyHandler::~EnemyHandler()
{
  for(auto &e : enemies_){
    e->Clean();
  }
}

void EnemyHandler::Init(){
  spawn_timer_.Init(1000);
  SpawnEnemy(Enemy::TOWARD_MIDDLE, 0.1);
}

void EnemyHandler::PauseSw(){
  spawn_timer_.PauseSw();
}

void EnemyHandler::HandleEvents(SDL_Event &e){

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
      e->setDead(true);
      player_->Damage();
    }

    if(!e->isDead() && player_shot_){
      Physics::Vec2D ray_start;
      Physics::Vec2D ray_end;
      player_->RayPoints(ray_start, ray_end);

      //check ray collision
      if(Physics::CollisionRayCircle(ray_start,ray_end, e->getCircle())){
        //increment score here

        e->setDead(true);
      }
    }

    // check for collision with player
    if(!e->isDead() && Physics::CollisionCircleCircle(player_->getCircle(), e->getCircle())){
      player_->Damage();
    }
  }
  player_shot_ = false;

  //clear dead enemies from vector.
  enemies_.erase(std::remove_if(enemies_.begin(), enemies_.end(),
                                [](auto e) {
                                  return e->isDead();
                                }), enemies_.end());

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
void EnemyHandler::Reset(){
  //pretty much done by deleting the enemies
  Clean();
  spawn_timer_.Reset();
  is_spawning_ = true;
}

void EnemyHandler::Clean(){
  //Will destroy the pointees - textures are freed in GameObject destructor
  enemies_.clear();
}

void EnemyHandler::SpawnEnemy(Enemy::TYPE enemy_type, float initial_speed){

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

  //different starting velocity for different types of enemies
  Physics::Vec2D vel = {0.0, 0.0};
  switch(enemy_type){
  case Enemy::TOWARD_MIDDLE:
    //position of screen centre - position of enemy centre
    vel = Physics::Vec2D(screen_width / 2, screen_height / 2) - Physics::Centre(spawn_rect);
    Physics::Normalize(vel);
    vel = vel * initial_speed;
    break;
  case Enemy::TEST:
    spawn_rect.x = screen_width/2;
    spawn_rect.y = screen_height/2;
    //leave velocity as zero
  default:
    break;
  }

  enemies_.push_back(std::make_shared<Enemy>(enemy_type, renderer_, window_, "../rad-shooter-POC/assets/enemy.png", spawn_rect,vel));
}

/*
 * This changes the timing of when ray collision is checked
 * right now checking after enemies move, but here would be before
 * So keep the player_shot_ bool, but set here instead of on mousepress
*/
void EnemyHandler::onNotify(GameObject *obj, EVENT_TYPE event_type){
  //game object will be player
  switch(event_type){
  case EVENT_TYPE::PLAYER_SHOT:
    player_shot_ = true;
    break;
  case EVENT_TYPE::PLAYER_DEAD:
    is_spawning_ = false;
    break;
  default:
    break;
  }
}

