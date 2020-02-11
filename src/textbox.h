#ifndef TEXTBOX_H
#define TEXTBOX_H

#include <SDL_ttf.h>
#include "gameobject.h"

class TextBox
{
public:
  TextBox(SDL_Renderer* rend, std::string initial_text, SDL_Rect intial_dest_rect);

  void Update();
  void Render();
  void Clean();

private:
  TTF_Font* font_;
  SDL_Color colour_;

  SDL_Renderer* renderer_;
  SDL_Texture* texture_;
  SDL_Rect dest_rect;
};

#endif // TEXTBOX_H
