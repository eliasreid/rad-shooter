#include <sstream>
#include "healthui.h"
#include "player.h"

HealthUI::HealthUI(SDL_Renderer* rend, std::string initial_text, int x_pos, int y_pos) :
  TextBox(rend, initial_text, x_pos, y_pos)
{

}

void HealthUI::onNotify(GameObject* obj, EVENT_TYPE event_type){
  //player has been damaged, -- health in text
  std::stringstream new_text;
  auto player = dynamic_cast<Player*>(obj);
  switch(event_type){
  case EVENT_TYPE::HEALTH_CHANGED:
    new_text << "Health: " << player->getHealth();
    UpdateText(new_text.str());
    break;
  }
}
