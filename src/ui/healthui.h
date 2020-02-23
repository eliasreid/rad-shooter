#ifndef HEALTHUI_H
#define HEALTHUI_H

#include <memory>
#include "gameobject.h"
#include "textbox.h"
#include "observer.h"
#include "event.h"

class HealthUI :  public Observer
{
public:
  HealthUI(SDL_Renderer* rend, SDL_Window* window, std::string initial_text, TextBox::SCREEN_POS pos, int font_size);
  ~HealthUI();

  void Render();

private:
  std::unique_ptr<TextBox> text_box_;

  void onNotify(GameObject* obj, EVENT_TYPE event_type) override;
};

#endif // HEALTHUI_H
