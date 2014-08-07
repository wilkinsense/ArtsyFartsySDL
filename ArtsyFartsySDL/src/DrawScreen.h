#pragma once

#include "ScreenManager.h"

class DrawScreen : public Screen
{
public:
  DrawScreen();
  ~DrawScreen();

  void OnEnter();
  void OnExit();
  
  void Update(const SDL_EventType &type);
  void Draw(SDL_Renderer *renderer);
};