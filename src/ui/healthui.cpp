#include <sstream>
#include "healthui.h"
#include "player.h"

HealthUI::HealthUI(SDL_Renderer* rend, SDL_Window* window, std::string initial_text, TextBox::SCREEN_POS pos, int font_size) :
  text_box_(std::make_unique<TextBox>(rend, window, initial_text, pos, font_size))
{

}

HealthUI::~HealthUI(){
  text_box_->Clean();
}

void HealthUI::Render(){
  text_box_->Render();
}

void HealthUI::onNotify(GameObject* obj, EVENT_TYPE event_type){
  //player has been damaged, -- health in text
  auto player = dynamic_cast<Player*>(obj);
  switch(event_type){
  case EVENT_TYPE::HEALTH_CHANGED:{
    std::stringstream new_text;
    new_text << "Health: " << player->getHealth();
    text_box_->UpdateText(new_text.str());
    break;
  }
  default:
    break;
  }
}

