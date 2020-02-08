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
  struct Vec2D{
    float x, y;
    Vec2D(): x(0), y(0){};
    Vec2D(float x, float y){
      this->x = x;
      this->y = y;
    };

    Vec2D operator+(const Vec2D &other){
      return Vec2D(x+other.x, y+other.y);
    }
    Vec2D operator-(const Vec2D &other) {
        return Vec2D(x-other.x, y-other.y);
    }
    Vec2D operator+(const Vec2D &other) const{
        return Vec2D(x+other.x, y+other.y);
    }
    Vec2D operator-(const Vec2D &other) const{
        return Vec2D(x-other.x, y-other.y);
    }
    //Scaling
    Vec2D operator*(float s){
      return Vec2D(x*s, y*s);
    }
    Vec2D operator/(float s){
      return Vec2D(x/s, y/s);
    }
  };

  struct Circle{
      Vec2D ctr;
      float rad;
  };

  void UpdateTime();

  static int frametime_ms;

  //Public functions
  static void Move(Vec2D &pos, Vec2D vel);
  static void Move(float &pos, float vel);

  static void Normalize(Vec2D &vec);
  static float Length(const Vec2D &vec);
  static float Length(float x, float y);
  static Vec2D Centre(SDL_Rect r);

  static bool CollisionCircleCircle(const Circle &c1, const Circle &c2);
  static bool CollisionRayCircle(const Vec2D &p1, const Vec2D &p2, const Circle &c);
  static float Dot(const Vec2D &p1, const Vec2D &p2);

private:
  std::chrono::high_resolution_clock::time_point prev_time;
};

#endif // PHYSICS_H
