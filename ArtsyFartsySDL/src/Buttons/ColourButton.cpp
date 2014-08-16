#include "ColourButton.h"
#include <SDL.h>
#include <SDL2_gfxPrimitives.h>

ColourButton::ColourButton(SDL_Texture *buttonTexture, ColorRGBA colour, int x, int y)
{
  mButtonTexture = buttonTexture;
  mButtonColor = colour;
  
  SetX(x);
  SetY(y);
}

void ColourButton::Draw(SDL_Renderer *renderer)
{
  int width = 60, height = 60;
  int halfWidth = width / 2, halfHeight = height / 2;
  int size = ((float)halfWidth * 0.94f);

  filledCircleRGBA(renderer, mPositionX + halfWidth, mPositionY + halfHeight, size, mButtonColor.r, mButtonColor.g, mButtonColor.b, mButtonColor.a);
  aacircleRGBA(renderer, mPositionX + halfWidth, mPositionY + halfHeight, size, mButtonColor.r, mButtonColor.g, mButtonColor.b, mButtonColor.a);
  
  SDL_Rect rect = { mPositionX, mPositionY, width, height };
  SDL_RenderCopy(renderer, mButtonTexture, NULL, &rect);
}

ColorRGBA ColourButton::GetColor()
{
  return mButtonColor;
}

void ColourButton::SetX(int x)
{
  mPositionX = x;
}

void ColourButton::SetY(int y)
{
  mPositionY = y;
}