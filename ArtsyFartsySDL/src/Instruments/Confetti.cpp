#include "Confetti.h"
#include <SDL.h>
#include <SDL2_gfxPrimitives.h>
#include "../Shape.h"

void Confetti::DrawShape(SDL_Renderer *renderer, Shape *shape)
{
  const std::vector<ShapeBlock *>* shapeBlocks = shape->GetBlocks();

  for (unsigned int blockIndex = 0; blockIndex < shapeBlocks->size(); blockIndex++)
  {
    ShapeBlock *firstBlock = shapeBlocks->at(blockIndex);
    ShapeBlock *secondBlock = nullptr;
    bool willDraw = firstBlock->drawn == false;

    if (blockIndex + 1 < shapeBlocks->size())
    {
      secondBlock = shapeBlocks->at(blockIndex + 1);
    }
    else if (shapeBlocks->size() > 1)
    {
      continue;
    }

    if (willDraw)
    {
      DrawBlock(renderer, firstBlock, secondBlock);
      firstBlock->drawn = true;
    }
  }
}

void Confetti::DrawBlock(SDL_Renderer *renderer, ShapeBlock *firstBlock, ShapeBlock *secondBlock)
{
  int x1 = firstBlock->x;
  int y1 = firstBlock->y;
  int x2 = firstBlock->x;
  int y2 = firstBlock->y;
  int size = firstBlock->brushSize;
  ColorRGBA color = firstBlock->brushColor;

  if (secondBlock != nullptr)
  {
    x2 = secondBlock->x;
    y2 = secondBlock->y;
  }

  int variance = size * 10;
  int offset = variance / 2;//(size * 5);

  thickLineRGBA(renderer,
    x1 + (rand() % variance) - offset,
    y1 + (rand() % variance) - offset,
    x2 + (rand() % variance) - offset,
    y2 + (rand() % variance) - offset,
    size,
    color.r - (rand() % 50),
    color.g - (rand() % 50),
    color.b - (rand() % 50),
    color.a);
}