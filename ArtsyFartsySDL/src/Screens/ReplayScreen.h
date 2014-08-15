#pragma once

#include "Screen.h"
#include "../Instrument.h"
#include <map>
#include <SDL_types.h>

class Shape;

class ReplayScreen : public Screen
{
public:
  ReplayScreen();
  ~ReplayScreen();

  void OnEnter();

  void Update(const SDL_Event &e);
  void Draw(SDL_Renderer *renderer);

protected:
  std::map<int, Instrument *> mInstruments;

  Uint32 mLastTimestamp;
  Uint32 mCurrentTimestamp;
  
  Uint16 mShapeIndex;
  Uint32 mBlockIndex;
};