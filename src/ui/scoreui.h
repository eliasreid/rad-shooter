#ifndef SCOREUI_H
#define SCOREUI_H

#include <memory>
#include "textbox.h"
#include "observer.h"

class ScoreUI : public Observer
{
public:
  ScoreUI(SDL_Renderer* rend, SDL_Window* window, std::string initial_text, TextBox::SCREEN_POS pos, int font_size);
  ~ScoreUI();

  void Render();
  void Reset();

private:
  std::unique_ptr<TextBox> text_box_;
  int score;

  void onNotify(GameObject *obj, EVENT_TYPE event_type) override;


};

#endif // SCOREUI_H
