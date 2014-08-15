#include "ColourButton.h"
#include <SDL.h>
#include <SDL2_gfxPrimitives.h>

ColourButton::ColourButton(SDL_Texture *buttonTexture, ColorRGBA colour)
{
  mButtonTexture = buttonTexture;
  mButtonColor = colour;
}

void ColourButton::Draw(SDL_Renderer *renderer, int x, int y)
{
  int width = 60, height = 60;
  int halfWidth = width / 2, halfHeight = height / 2;
  int size = ((float)halfWidth * 0.93f);

  filledCircleRGBA(renderer, x + halfWidth, y + halfHeight, size, mButtonColor.r, mButtonColor.g, mButtonColor.b, mButtonColor.a);
  aacircleRGBA(renderer, x + halfWidth, y + halfHeight, size, mButtonColor.r, mButtonColor.g, mButtonColor.b, mButtonColor.a);
  aacircleRGBA(renderer, x + halfWidth, y + halfHeight, size, mButtonColor.r, mButtonColor.g, mButtonColor.b, mButtonColor.a);

  SDL_Rect rect = { x, y, width, height };
  SDL_RenderCopy(renderer, mButtonTexture, NULL, &rect);
}

ColorRGBA ColourButton::GetColor()
{
  return mButtonColor;
}
