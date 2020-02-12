#include <iostream>
#include "textbox.h"

TextBox::TextBox(SDL_Renderer* rend, std::string initial_text, int x_pos, int y_pos)
{
  colour_ = {0,0,0,255}; // initialize text as black
  renderer_ = rend;
  texture_ = nullptr;
  font_ = nullptr;
  dest_rect_.x = x_pos;
  dest_rect_.y = y_pos;
  font_ = TTF_OpenFont("../rad-shooter-POC/assets/lazy.ttf", 40); //Should be option, either Init or in constructor
  if(font_ == nullptr){
    printf( "Failed to load font! SDL_ttf Error: %s\n", TTF_GetError() );
  }else{
    //Initialize texture based on the given text
    UpdateText(initial_text);
  }

}

void TextBox::UpdateText(std::string new_text, int font_size){

  //reload font with new given size.
  if(font_size > 0){
    font_ = TTF_OpenFont("../rad-shooter-POC/assets/lazy.ttf", font_size); //Should be option, either Init or in constructor
  }

  //recreate texture using loaded font and text
  SDL_Surface* text_surface = TTF_RenderText_Solid(font_, new_text.c_str(), colour_);

  if(text_surface == nullptr){
    std::cerr << "Unable to render text surface! SDL_ttf Error:: " << TTF_GetError() << std::endl;
  }
  else{
    //Create texture from surface
    texture_ = SDL_CreateTextureFromSurface(renderer_, text_surface);
    if(texture_ == nullptr){
      std::cerr << "Unable to create texture from rendered text! SDL Error: " << SDL_GetError() << std::endl;
    } else{
      dest_rect_.w = text_surface->w;
      dest_rect_.h = text_surface->h;
    }

    SDL_FreeSurface(text_surface);
  }
}

void TextBox::UpdatePos(int x_pos, int y_pos){
  dest_rect_.x = x_pos;
  dest_rect_.y = y_pos;
}

void TextBox::Render(){
  if(texture_ != nullptr){
    SDL_RenderCopy(renderer_, texture_, nullptr, &dest_rect_);
  }
}
void TextBox::Clean(){
  if(texture_ != nullptr){
    SDL_DestroyTexture(texture_);
    texture_ = nullptr;
  }
}

