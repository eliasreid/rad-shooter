#include <iostream>
#include "physics.h"

int Physics::frametime_ms  = 0;

Physics::Physics() : prev_time(std::chrono::high_resolution_clock::now()){

}

void Physics::Move(Vec2D &pos, Vec2D vel){
  pos.x += frametime_ms * vel.x;
  pos.y += frametime_ms * vel.y;
}

void Physics::Move(float &pos, float vel){
  pos += frametime_ms * vel;
}

void Physics::UpdateTime(){
  auto current_time = std::chrono::high_resolution_clock::now();
  frametime_ms = std::chrono::duration_cast<std::chrono::milliseconds>(current_time - prev_time).count();
  prev_time = current_time;
}

void Physics::Normalize(Vec2D &vec){
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

bool Physics::CollisionCircleCircle(const Circle &c1, const Circle &c2){
    // distance between points - is it greater than sum of radii?

//    auto newVec = c1-c2;
//    float distance =

    return Length(c1.ctr-c2.ctr) < (c1.rad+c2.rad);
}
/**
 * @brief Physics::CollisionRayCircle
 * @param p1 - start of line segment
 * @param p2 - end of line segment
 * @param c2 - circle to check collision with
 *
 * Doesn't work for arbitrary line segment - assumes that closest point on
 * ray to enemy is never the start / end point. ok to do in our case
 *
 * @return
 */

bool Physics::CollisionRayCircle(const Vec2D &p1, const Vec2D &p2, const Circle &c){

  Vec2D ray_vec = p2-p1;
  Vec2D vec_to_start = p1 - c.ctr;

  if(Dot(ray_vec,vec_to_start) > 0){
    //enemy "behind" player - so don't bother checking
    return false;
  }

  float dist_from_line;
  float proj_on_ray = Dot(ray_vec, vec_to_start);
  Vec2D vec_from_end = c.ctr - p2;

  Vec2D e = vec_to_start - ray_vec * ( proj_on_ray / Dot(ray_vec, ray_vec));
  if(Length(e) < c.rad){
    return true;
  }
  return false;
}

float Physics::Dot(const Vec2D &v1, const Vec2D &v2){
  return v1.x * v2.x + v1.y * v2.y;
}
