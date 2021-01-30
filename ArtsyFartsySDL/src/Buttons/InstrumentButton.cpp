#include "InstrumentButton.h"
#include <SDL.h>
#include <SDL2_gfxPrimitives.h>

InstrumentButton::InstrumentButton(SDL_Texture* buttonTexture, int x, int y) : SelectableButton(buttonTexture, x, y)
{
}

void InstrumentButton::Draw(SDL_Renderer* renderer)
{
    int width = 60, height = 60;
    int halfWidth = width / 2, halfHeight = height / 2;

    SDL_Rect rect = { mPositionX, mPositionY, width, height };
    SDL_RenderCopy(renderer, mButtonTexture, NULL, &rect);
}
