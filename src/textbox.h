#ifndef TEXTBOX_H
#define TEXTBOX_H
#include <string>
#include <SDL_ttf.h>

class TextBox
{
public:
  TextBox(SDL_Renderer* rend, std::string initial_text, int x_pos, int y_pos);

  void UpdateText(std::string new_text, int font_size =0);
  void UpdatePos(int x_pos, int y_pos);
  void Render();
  void Clean();

private:
  TTF_Font* font_;
  SDL_Color colour_;

  SDL_Renderer* renderer_;
  SDL_Texture* texture_;
  SDL_Rect dest_rect_;
};

#endif // TEXTBOX_H