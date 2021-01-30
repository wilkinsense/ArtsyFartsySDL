#include "Eraser.h"
#include "../Shape.h"
#include <SDL.h>
#include <SDL2_gfxPrimitives.h>

void Eraser::DrawShape(SDL_Renderer* renderer, Shape* shape, bool incremental)
{
    const std::vector<ShapeBlock*>* shapeBlocks = shape->GetBlocks();

    for (unsigned int blockIndex = 0; blockIndex < shapeBlocks->size(); blockIndex++)
    {
        ShapeBlock* firstBlock = shapeBlocks->at(blockIndex);
        ShapeBlock* secondBlock = nullptr;
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

            if (incremental == true)
            {
                break;
            }
        }
    }
}

void Eraser::DrawBlock(SDL_Renderer* renderer, ShapeBlock* firstBlock, ShapeBlock* secondBlock)
{
    int x1 = firstBlock->x;
    int y1 = firstBlock->y;
    int size = firstBlock->brushSize;

    filledCircleRGBA(renderer,
        x1, y1, size,
        0xFF, 0xFF, 0xFF, 0xFF);

    aacircleRGBA(renderer,
        x1, y1, size,
        0xFF, 0xFF, 0xFF, 0xFF);
}