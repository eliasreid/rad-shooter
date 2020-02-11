#include "gameobject.h"
#include <iostream>

GameObject::GameObject(SDL_Renderer* rend, std::string texture_path, SDL_Rect intial_dest_rect)
{
  renderer_ = rend;
  texture_ = nullptr;
  SDL_Surface* tempS = IMG_Load(texture_path.c_str());

  if(tempS == nullptr){
    std::cerr << "Unable to load image at" << texture_path << "! SDL_image Error: " << IMG_GetError() << std::endl;
  }
  else{
    //Create texture from surface
    texture_ = SDL_CreateTextureFromSurface(renderer_, tempS);
    if(texture_ == nullptr){
      std::cerr << "Unable to create texture from " << texture_path << "! SDL Error: " << SDL_GetError() << std::endl;
    }

    //set default dest_rect
    dest_rect = intial_dest_rect;

    SDL_FreeSurface(tempS);
  }
}

void GameObject::Update(){

}

void GameObject::Render(){
  if(texture_ != nullptr){
    SDL_RenderCopy(renderer_, texture_, nullptr, &dest_rect);
  }

}
void GameObject::Clean(){
  if(texture_ != nullptr){
    SDL_DestroyTexture(texture_);
    texture_ = nullptr;
  }
}
