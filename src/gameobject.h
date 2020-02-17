#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include <SDL.h>
#include <SDL_image.h>
#include <string>

class GameObject
{
public:
  GameObject(SDL_Renderer* rend, std::string texture_path,  SDL_Rect intial_dest_rect);
  ~GameObject();
  virtual void Update();
  virtual void Render();
  virtual void Clean();

protected:
  SDL_Renderer* renderer_;
  SDL_Texture* texture_;
  SDL_Rect dest_rect;

  //in vid he had srcRect adn destRect members in the GO class.

};

#endif // GAMEOBJECT_H
