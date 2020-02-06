#include "physics.h"

int Physics::frametime_ms  = 0;

Physics::Physics() : prev_time(std::chrono::high_resolution_clock::now()){

}

void Physics::Move(Vec2D &pos, Vec2D vel){
  pos.x += frametime_ms * vel.x;
  pos.y += frametime_ms * vel.y;
}

void Physics::Move(float &pos, float vel){
  pos = frametime_ms * vel;
}

void Physics::UpdateTime(){
  auto current_time = std::chrono::high_resolution_clock::now();
  frametime_ms = std::chrono::duration_cast<std::chrono::milliseconds>(current_time - prev_time).count();
}

void Physics::Normalize(Vec2D &vec){
  //calc length, divide both elements by that length

  vec = vec / Length(vec);
}

float Physics::Length(const Vec2D &vec){
  return sqrt(pow(vec.x,2) + pow(vec.y,2));
}

float Physics::Length(float x, float y){
  return sqrt(pow(x,2) + pow(y,2));
}

/*
 * For calclulating the centre of an SDL_Rect
*/
Physics::Vec2D Physics::Centre(SDL_Rect r){
  return Vec2D(r.x + r.w/2.0, r.y + r.h/2.0);
}
