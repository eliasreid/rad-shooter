#include <iostream>
#include "textbox.h"

TextBox::TextBox(SDL_Renderer* rend, std::string initial_text, SDL_Rect intial_dest_rect)
{
  colour_ = {0,0,0,255}; // initialize text as black
  renderer_ = rend;
  texture_ = nullptr;
  font_ = nullptr;
  SDL_Surface* text_surface = TTF_RenderText_Solid(font_, initial_text.c_str(), colour_);

  if(text_surface == nullptr){
    std::cerr << "Unable to redner text surface! SDL_ttf Error:: " << TTF_GetError() << std::endl;
  }
  else{
    //Create texture from surface
    texture_ = SDL_CreateTextureFromSurface(renderer_, text_surface);
    if(texture_ == nullptr){
      std::cerr << "Unable to create texture from rendered text! SDL Error: " << SDL_GetError() << std::endl;
    }

    //set default dest_rect
    dest_rect = intial_dest_rect;

    SDL_FreeSurface(text_surface);
  }

}

void TextBox::Update(){

}

void TextBox::Render(){
  if(texture_ != nullptr){
    SDL_RenderCopy(renderer_, texture_, nullptr, &dest_rect);
  }

}
void TextBox::Clean(){
  if(texture_ != nullptr){
    SDL_DestroyTexture(texture_);
    texture_ = nullptr;
  }
}
