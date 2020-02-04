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
