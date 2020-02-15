#ifndef HEALTHUI_H
#define HEALTHUI_H

#include "textbox.h"
#include "observer.h"

class HealthUI : public TextBox, public Observer
{
public:
  HealthUI(SDL_Renderer* rend, std::string initial_text, int x_pos, int y_pos);

private:
  void onNotify() override;
  int health_;
};

#endif // HEALTHUI_H
