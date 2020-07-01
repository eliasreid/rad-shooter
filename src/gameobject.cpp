#include "gameobject.h"
#include <iostream>

GameObject::GameObject(SDL_Renderer* rend, std::string texture_path, SDL_Rect intial_dest_rect)
: texture_mode_(UNIQUE)
{
  renderer_ = rend;
  texture_ = nullptr;
  SDL_Surface* temp_surface = IMG_Load(texture_path.c_str());

  if(temp_surface == nullptr){
    std::cerr << "Unable to load image at" << texture_path << "! SDL_image Error: " << IMG_GetError() << std::endl;
  }
  else{
    //Create texture from surface
    texture_ = SDL_CreateTextureFromSurface(renderer_, temp_surface);
    if(texture_ == nullptr){
      std::cerr << "Unable to create texture from " << texture_path << "! SDL Error: " << SDL_GetError() << std::endl;
    }

    //set default dest_rect
    dest_rect_ = intial_dest_rect;

    SDL_FreeSurface(temp_surface);
  }
}

/**
 * @brief GameObject::GameObject overload provides the option to instantiate GameObject with existing texture
 * @param rend
 * @param preloaded_texture
 * @param intial_dest_rect
 */
GameObject::GameObject(SDL_Renderer* rend, SDL_Texture* preloaded_texture, SDL_Rect intial_dest_rect)
    : texture_mode_(SHARED)
{
  renderer_ = rend;
  texture_ = preloaded_texture;

  //set default dest_rect
  dest_rect_ = intial_dest_rect;

}

GameObject::~GameObject(){
  Clean();
}

void GameObject::Update(){

}

void GameObject::Render(){
  if(texture_ != nullptr){
    SDL_RenderCopy(renderer_, texture_, nullptr, &dest_rect_);
  }

}
void GameObject::Clean(){
  if(texture_mode_ == UNIQUE && texture_ != nullptr){
    SDL_DestroyTexture(texture_);
    texture_ = nullptr;
  }
}
