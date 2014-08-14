#pragma once

#include "ColorHelper.h"

struct SDL_Renderer;
class Shape;
struct ShapeBlock;

class Instrument
{
public:
  virtual void DrawShape(SDL_Renderer *renderer, Shape *shape) = 0;
  virtual void DrawBlock(SDL_Renderer *renderer, ShapeBlock *firstBlock, ShapeBlock *secondBlock) = 0;
};