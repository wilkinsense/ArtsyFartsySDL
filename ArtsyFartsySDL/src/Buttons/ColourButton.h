#pragma once
#include "../ColorHelper.h"

struct SDL_Texture;
struct SDL_Renderer;

class ColourButton
{
public:
  ColourButton(SDL_Texture *buttonTexture, ColorRGBA color, int x, int y);

  void Draw(SDL_Renderer *renderer);
  ColorRGBA GetColor();

  void SetX(int x);
  void SetY(int y);

protected:
  int mPositionX;
  int mPositionY;

  SDL_Texture *mButtonTexture;
  ColorRGBA mButtonColor;
};