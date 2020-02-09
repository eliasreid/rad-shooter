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
//  std::cout << "frametime: " << frametime_ms;
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
 * This is acutally over complicated. dont need to consider line segment
 * can just check that the enemy is not "behind" the player, then just
 * distance from line (described by two points (on wikipedia)
 * https://en.wikipedia.org/wiki/Distance_from_a_point_to_a_line
 *
 * @return
 */

bool Physics::CollisionRayCircle(const Vec2D &p1, const Vec2D &p2, const Circle &c){

  std::cout << "Checking collision... ";

  Vec2D ray_vec = p2-p1;
  Vec2D vec_to_start = p1 - c.ctr;

  //initial check
  if(Dot(ray_vec,vec_to_start) > 0){
    //enemy "behind" player - so don't bother checking
    std::cout << "wrong side." <<std::endl;
    return false;
  }
  std::cout << "right side... ";
//  Normalize(ray_vec);

//  float dist = Length(vec_to_start - ray_vec*Dot(vec_to_start,ray_vec));

//  if(dist < c.rad){
//    std::cout << "Collision!" << std::endl;
//    return true;
//  }

  //Should be able to use simple point to line


  float dist_from_line;

  float proj_on_ray = Dot(ray_vec, vec_to_start);

  Vec2D vec_from_end = c.ctr - p2;

  //closest point on line is ray end
  if(Dot(ray_vec, vec_from_end) > 0){
    dist_from_line = Length(vec_from_end);
    if(dist_from_line < c.rad){
      std::cout << "Collision!" << std::endl;
      return true;
    }else{
      return false;
    }
  }

  //so closest point is actually between
  Vec2D e = vec_to_start - ray_vec * ( proj_on_ray / Dot(ray_vec, ray_vec));

  if(Length(e) < c.rad){
    std::cout << "Collision!" << std::endl;
    return true;
  }
  std::cout << "no collision." << std::endl;
  return false;
}

float Physics::Dot(const Vec2D &v1, const Vec2D &v2){
  return v1.x * v2.x + v1.y * v2.y;
}
