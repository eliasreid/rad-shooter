#ifndef TEXTBOX_H
#define TEXTBOX_H
#include <string>
#include <SDL.h>
#include <SDL_ttf.h>

class TextBox
{
public:
  enum class SCREEN_POS{
    CENTRE,
    TOP_LEFT,
    TOP_RIGHT,
    BOTTOM_LEFT,
    BOTTOM_RIGHT
  };

  TextBox(SDL_Renderer* rend, SDL_Window* window, std::string initial_text, int x_pos, int y_pos, int font_size, bool is_visible = true);
  TextBox(SDL_Renderer* rend, SDL_Window* window, std::string initial_text, SCREEN_POS pos, int font_size, bool is_visible = true);
  ~TextBox();

  void UpdateText(std::string new_text, int font_size =0);
  void UpdatePos(int x_pos, int y_pos, bool centered = false);
  void Render();
  void Clean();

  void setVisible(bool visible);

private:
  TTF_Font* font_;
  SDL_Color colour_;

  SDL_Renderer* renderer_;
  SDL_Window* window_;
  SDL_Texture* texture_;
  SDL_Rect dest_rect_;
  bool is_visible_;
};

#endif // TEXTBOX_H
