#ifndef HEALTHUI_H
#define HEALTHUI_H

#include "gameobject.h"
#include "textbox.h"
#include "observer.h"
#include "event.h"

class HealthUI : public TextBox, public Observer
{
public:
  HealthUI(SDL_Renderer* rend, SDL_Window* window, std::string initial_text, SCREEN_POS pos, int font_size);

private:
  void onNotify(GameObject* obj, EVENT_TYPE event_type) override;
};

#endif // HEALTHUI_H
