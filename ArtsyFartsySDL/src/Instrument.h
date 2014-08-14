#pragma once

#include "ColorHelper.h"
#include <SDL_types.h>

struct SDL_Renderer;
class Shape;
struct ShapeBlock;

class Instrument
{
public:
  virtual void DrawShape(SDL_Renderer *renderer, Shape *shape, bool incremental = false) = 0;
  virtual void DrawBlock(SDL_Renderer *renderer, ShapeBlock *firstBlock, ShapeBlock *secondBlock) = 0;

protected:
  Uint32 mShapeTimestamp;
  Uint32 mLastIncrementalTimestamp;
  Shape *mLastIncrementalShape;
};