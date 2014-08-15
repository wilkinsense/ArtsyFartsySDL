#pragma once

#include <SDL_events.h>
struct SDL_Renderer;

class Screen
{
public:
  Screen();
  ~Screen();

  virtual void Update(const SDL_Event &e) = 0;
  virtual void Draw(SDL_Renderer *renderer) = 0;

  virtual void OnEnter() { }
  virtual void OnExit() { }
};