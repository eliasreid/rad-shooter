#include <iostream>
#include "textbox.h"

TextBox::TextBox(SDL_Renderer* rend, SDL_Window* window, std::string initial_text, int x_pos, int y_pos, int font_size, bool is_visible)
    : is_visible_(is_visible), window_(window)
{
  colour_ = {0,0,0,255}; // initialize text as black
  renderer_ = rend;
  texture_ = nullptr;
  font_ = nullptr;
  dest_rect_.x = x_pos;
  dest_rect_.y = y_pos;
  dest_rect_.h = 0;
  dest_rect_.w = 0;
  font_ = TTF_OpenFont("../rad-shooter-POC/assets/lazy.ttf", font_size); //Should be option, either Init or in constructor
  if(font_ == nullptr){
    printf( "Failed to load font! SDL_ttf Error: %s\n", TTF_GetError() );
  }else{
    //Initialize texture based on the given text
    UpdateText(initial_text);
  }
}

TextBox::TextBox(SDL_Renderer* rend, SDL_Window* window, std::string initial_text, SCREEN_POS pos, int font_size, bool is_visible)
    : is_visible_(is_visible), window_(window)
{
  colour_ = {0,0,0,255}; // initialize text as black
  renderer_ = rend;
  texture_ = nullptr;
  font_ = nullptr;
  dest_rect_.h = 0;
  dest_rect_.w = 0;
  font_ = TTF_OpenFont("../rad-shooter-POC/assets/lazy.ttf", font_size); //Should be option, either Init or in constructor
  if(font_ == nullptr){
    printf( "Failed to load font! SDL_ttf Error: %s\n", TTF_GetError() );
  }else{
    //Initialize texture based on the given text
    UpdateText(initial_text);
    //if UpdateText was successful, we should have a height and width for the box
    if((dest_rect_.w != 0) && (dest_rect_.h != 0)){

      int screen_width, screen_height;
      SDL_GetWindowSize(window_, &screen_width, &screen_height);
      //TODO: test this
      switch(pos){
      case SCREEN_POS::CENTRE:
        //need screen dimensions
        UpdatePos(screen_width/2, screen_height/2, true);
        break;
      case SCREEN_POS::TOP_LEFT:
        UpdatePos(0,0);
        break;
      case SCREEN_POS::TOP_RIGHT:
        UpdatePos(screen_width - dest_rect_.w, 0);
        break;
      case SCREEN_POS::BOTTOM_LEFT:
        UpdatePos(0, screen_width - dest_rect_.h);
        break;
      case SCREEN_POS::BOTTOM_RIGHT:
        UpdatePos(screen_width - dest_rect_.w, screen_width - dest_rect_.h);
        break;
      }
    } else{
      std::cerr << "Error initializing TextBox" << std::endl;
      dest_rect_.x = 0;
      dest_rect_.y = 0;
    }

  }
}

TextBox::~TextBox(){
  Clean();
}

/**
 * @brief TextBox::UpdateText
 * @param new_text
 * @param font_size - leave unchanged if 0
 */
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
/**
 * @brief TextBox::UpdatePos
 * @param x_pos
 * @param y_pos
 * @param centered - if true, use x_pos, y_pos as centre of dest_rect
 */
void TextBox::UpdatePos(int x_pos, int y_pos, bool centered){
  if(!centered){
    dest_rect_.x = x_pos;
    dest_rect_.y = y_pos;
  } else{
    dest_rect_.x = x_pos - dest_rect_.w/2;
    dest_rect_.y = y_pos - dest_rect_.h/2;
  }
}

void TextBox::Render(){
  if(texture_ != nullptr && is_visible_){
    SDL_RenderCopy(renderer_, texture_, nullptr, &dest_rect_);
  }
}
void TextBox::Clean(){
  if(texture_ != nullptr){
    SDL_DestroyTexture(texture_);
    texture_ = nullptr;
  }
}

void TextBox::setVisible(bool visible){
  is_visible_ = visible;
}
