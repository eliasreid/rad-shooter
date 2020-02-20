#include <sstream>
#include "healthui.h"
#include "player.h"

HealthUI::HealthUI(SDL_Renderer* rend, SDL_Window* window, std::string initial_text, SCREEN_POS pos, int font_size) :
  TextBox(rend, window, initial_text, pos, font_size)
{

}

void HealthUI::onNotify(GameObject* obj, EVENT_TYPE event_type){
  //player has been damaged, -- health in text
  auto player = dynamic_cast<Player*>(obj);
  switch(event_type){
  case EVENT_TYPE::HEALTH_CHANGED:{
    std::stringstream new_text;
    new_text << "Health: " << player->getHealth();
    UpdateText(new_text.str());
    break;
  }
  default:
    break;
  }
}
