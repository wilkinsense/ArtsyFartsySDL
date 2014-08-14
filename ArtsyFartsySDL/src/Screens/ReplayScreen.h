#pragma once

#include "Screen.h"
#include "../Instrument.h"
#include <map>

class ReplayScreen : public Screen
{
public:
  ReplayScreen();
  ~ReplayScreen();

  void OnEnter();

  void Update(const SDL_EventType &type);
  void Draw(SDL_Renderer *renderer);

protected:
  std::map<int, Instrument *> mInstruments;
};