#include "player.h"

Player::Player(SDL_Renderer* rend, std::string texture_path,  SDL_Rect intial_dest_rect, SDL_Window* window):GameObject(rend, texture_path, intial_dest_rect){

  window_ = window;
  int x_size, y_size;
  SDL_GetWindowSize(window_, &x_size, &y_size);
  ray_length = sqrt(pow(x_size,2) + pow(y_size,2));

  prev_time = std::chrono::high_resolution_clock::now();
  ray_velocity = 0.001; // will be an important gameplay parameter

}

void Player::HandleEvents(SDL_Event &e){

  if(e.type == SDL_MOUSEMOTION){
    int x, y;
    SDL_GetMouseState(&x, &y);

    //player should be centered on mouse - used to update render rect in Update()
    player_centre.x = x;
    player_centre.y = y;

  }
}

void Player::Update(){

  //Update player's render destination rect.
  dest_rect.x = player_centre.x - dest_rect.w/2;
  dest_rect.y = player_centre.y - dest_rect.h/2;

  //Calculating time since last frame to update ray angle from angular velocity
  auto current_time = std::chrono::high_resolution_clock::now();
  auto time_since_prev = std::chrono::duration_cast<std::chrono::milliseconds>(current_time - prev_time).count();
  prev_time = current_time;
  ray_angle += ray_velocity * time_since_prev;

  if(ray_angle > 360.0){
    ray_angle -= 360.0;
  }

  //Set ray endpoint based on new angle.
  ray_end.x = player_centre.x + ray_length * sin(ray_angle);
  ray_end.y = player_centre.y - ray_length * cos(ray_angle);
}

void Player::Render(){
  GameObject::Render();

  //Additional rendering for player class

  //Render ray cursor
  SDL_SetRenderDrawColor(renderer_,0,0,0,255);
  SDL_RenderDrawLine(renderer_, player_centre.x, player_centre.y, ray_end.x, ray_end.y);
}


