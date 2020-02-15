#include <sstream>
#include "healthui.h"

HealthUI::HealthUI(SDL_Renderer* rend, std::string initial_text, int x_pos, int y_pos) :
  TextBox(rend, initial_text, x_pos, y_pos)
{
  health_=4;
}

void HealthUI::onNotify(){
  //player has been damaged, -- health in text
  health_--;
  std::stringstream ss;
  ss << "Health: " << health_;
  UpdateText(ss.str());
}
