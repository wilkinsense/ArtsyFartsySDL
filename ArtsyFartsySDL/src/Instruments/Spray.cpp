#include "Spray.h"
#include <SDL.h>
#include <SDL2_gfxPrimitives.h>
#include "../Shape.h"

void Spray::DrawShape(SDL_Renderer *renderer, Shape *shape)
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
      if ((blockIndex == 0 && shapeBlocks->size() == 2))
      {
        willDraw = true;
      }
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

void Spray::DrawBlock(SDL_Renderer *renderer, ShapeBlock *firstBlock, ShapeBlock *secondBlock)
{
  int x1 = firstBlock->x;
  int y1 = firstBlock->y;
  int x2 = firstBlock->x;
  int y2 = firstBlock->y;
  int size = firstBlock->brushSize / 2;
  ColorRGBA color = firstBlock->brushColor;

  if (secondBlock != nullptr)
  {
    x2 = secondBlock->x;
    y2 = secondBlock->y;
    size = firstBlock->brushSize;
  }

  thickLineRGBA(renderer,
    x1, y1, x2, y2,
    size,
    color.r, color.g, color.b, color.a);
}