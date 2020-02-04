#ifndef PHYSICS_H
#define PHYSICS_H

#include <chrono>

/*
 * class for physics / timing functions
*/
class Physics
{
public:
  Physics();
  struct Vec2D{
    float x, y;
  };

  void UpdateTime();

  static int frametime_ms;

  //Public functions
  static void Move(Vec2D &pos, Vec2D vel);
  static void Move(float &pos, float vel);


private:
  std::chrono::high_resolution_clock::time_point prev_time;
};

#endif // PHYSICS_H
