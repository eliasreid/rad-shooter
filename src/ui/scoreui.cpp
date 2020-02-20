#include <sstream>
#include "scoreui.h"

ScoreUI::ScoreUI(SDL_Renderer* rend, SDL_Window* window, std::string initial_text, TextBox::SCREEN_POS pos, int font_size):
  text_box_(std::make_unique<TextBox>(rend, window, initial_text, pos, font_size)), score(0)
{

}

ScoreUI::~ScoreUI(){
  text_box_->Clean();
}

void ScoreUI::Render(){
  text_box_->Render();
}

void ScoreUI::Reset(){
  score = 0;
}

void ScoreUI::onNotify(GameObject *obj, EVENT_TYPE event_type){

  switch(event_type){
  case EVENT_TYPE::SCORE:{
    score++;
    std::stringstream new_text;
    new_text << "Score: " << score;
    text_box_->UpdateText(new_text.str());
    break;
  }
  default:
    break;
  }
}
