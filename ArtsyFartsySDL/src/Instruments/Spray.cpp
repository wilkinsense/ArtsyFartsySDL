#include "Spray.h"
#include "../Shape.h"
#include <SDL.h>
#include <SDL2_gfxPrimitives.h>

void Spray::DrawShape(SDL_Renderer* renderer, Shape* shape, bool incremental)
{
    const std::vector<ShapeBlock*>* shapeBlocks = shape->GetBlocks();

    for (unsigned int blockIndex = 0; blockIndex < shapeBlocks->size(); blockIndex++)
    {
        ShapeBlock* firstBlock = shapeBlocks->at(blockIndex);
        ShapeBlock* secondBlock = nullptr;
        bool willDraw = firstBlock->drawn == false;

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

void Spray::DrawBlock(SDL_Renderer* renderer, ShapeBlock* firstBlock, ShapeBlock* secondBlock)
{
    int x1 = firstBlock->x;
    int y1 = firstBlock->y;
    int size = firstBlock->brushSize;
    ColorRGBA color = firstBlock->brushColor;

    int variance = size * 10;
    int offset = variance / 2;//(size * 5);
    static int colorOffset = 50;
    static int halfOffset = colorOffset / 2;

    int rOffset = ((rand() % halfOffset));
    int gOffset = ((rand() % halfOffset));
    int bOffset = ((rand() % halfOffset));

    int r = color.r - rOffset;
    int g = color.g - gOffset;
    int b = color.b - bOffset;

    ColorRGBA newColor(r < 0 ? 0 : r,
        g < 0 ? 0 : g,
        b < 0 ? 0 : b,
        color.a);

    for (int i = 0; i < 10; i++)
    {
        int newSize = size + (rand() % 4) - 2;
        if (newSize < 1)
        {
            newSize = 1;
        }

        filledCircleRGBA(renderer,
            x1 + (rand() % variance) - offset,
            y1 + (rand() % variance) - offset,
            size + (rand() % 4) - 2,
            newColor.r, newColor.g, newColor.b, color.a);
    }
}