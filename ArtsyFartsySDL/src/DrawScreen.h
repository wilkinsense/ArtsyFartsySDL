#pragma once

#include "ScreenManager.h"
#include <map>

class Instrument;

class DrawScreen : public Screen
{
public:
  DrawScreen();
  ~DrawScreen();

  void OnEnter();
  void OnExit();
  
  void Update(const SDL_EventType &type);
  void Draw(SDL_Renderer *renderer);

protected:
  std::map<int, Instrument *> mInstruments;
};