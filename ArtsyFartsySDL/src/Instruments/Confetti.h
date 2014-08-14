#pragma once
#include "../Instrument.h"

struct ShapeBlock;

class Confetti: public Instrument
{
public:
  bool DrawShape(SDL_Renderer *renderer, Shape *shape, bool incremental = false);
  void DrawBlock(SDL_Renderer *renderer, ShapeBlock *firstBlock, ShapeBlock *secondBlock);
};