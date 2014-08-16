#include "SelectableButton.h"
#include <SDL.h>
#include <SDL2_gfxPrimitives.h>

SelectableButton::SelectableButton(SDL_Texture *buttonTexture, int x, int y)
{
  mButtonTexture = buttonTexture;
  SetX(x);
  SetY(y);
}

void SelectableButton::SetX(int x)
{
  mPositionX = x;
}

void SelectableButton::SetY(int y)
{
  mPositionY = y;
}

bool SelectableButton::IsPointWithinButton(int x, int y)
{
  int halfWidth = 30;
  bool foundInput = false;

  int diffX = abs(x - mPositionX - halfWidth);
  int diffY = abs(y - mPositionY - halfWidth);
  float diff = sqrtf((diffX * diffX) + (diffY * diffY));
  if (diff <= halfWidth)
  {
    foundInput = true;
  }

  return foundInput;
}
