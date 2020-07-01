#ifndef PHYSICS_H
#define PHYSICS_H

#include <chrono>
#include <SDL.h>

/*
 * class for physics / timing functions
*/
class Physics
{
public:
  Physics();
  struct Vec2{
    float x, y;
    Vec2(): x(0), y(0){};
    Vec2(float x, float y){
      this->x = x;
      this->y = y;
    };

    Vec2 operator+(const Vec2 &other){
      return Vec2(x+other.x, y+other.y);
    }
    Vec2 operator-(const Vec2 &other) {
        return Vec2(x-other.x, y-other.y);
    }
    Vec2 operator+(const Vec2 &other) const{
        return Vec2(x+other.x, y+other.y);
    }
    Vec2 operator-(const Vec2 &other) const{
        return Vec2(x-other.x, y-other.y);
    }
    //Scaling
    Vec2 operator*(float s){
      return Vec2(x*s, y*s);
    }
    Vec2 operator/(float s){
      return Vec2(x/s, y/s);
    }
  };

  struct Circle{
      Vec2 ctr;
      float rad;
  };

  void UpdateTime();

  static int frametime_ms;

  //Public functions
  static void Move(Vec2 &pos, Vec2 vel);
  static void Move(float &pos, float vel);

  static void Normalize(Vec2 &vec);
  static float Length(const Vec2 &vec);
  static float Length(float x, float y);
  static Vec2 Centre(SDL_Rect r);

  static bool CollisionCircleCircle(const Circle &c1, const Circle &c2);
  static bool CollisionRayCircle(const Vec2 &p1, const Vec2 &p2, const Circle &c);
  static float Dot(const Vec2 &p1, const Vec2 &p2);

private:
  std::chrono::high_resolution_clock::time_point prev_time;
};

#endif // PHYSICS_H
