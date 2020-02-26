#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include <string>
#include <memory>
#include <SDL.h>
#include <SDL_image.h>


class GameObject
{
public:
  GameObject(SDL_Renderer* rend, std::string texture_path,  SDL_Rect intial_dest_rect);
  GameObject(SDL_Renderer* rend, SDL_Texture* preloaded_texture,  SDL_Rect intial_dest_rect);
  ~GameObject();
  virtual void Update();
  virtual void Render();
  virtual void Clean();

protected:
  SDL_Renderer* renderer_;
  SDL_Texture* texture_;
  SDL_Rect dest_rect_;

private:
  /**
   * @brief The TEXTURE_MODE enum
   * Used to determine how to free texture on Clean(). If texture is a shared resource,
   * we shall not destroy it on destruction
   */
  enum TEXTURE_MODE{
    UNIQUE,
    SHARED
  } texture_mode_;

};

#endif // GAMEOBJECT_H
