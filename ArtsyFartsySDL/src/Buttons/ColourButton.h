#pragma once
#include "../ColorHelper.h"

struct SDL_Texture;
struct SDL_Renderer;

class ColourButton
{
public:
  ColourButton(SDL_Texture *buttonTexture, ColorRGBA color);

  void Draw(SDL_Renderer *renderer, int x, int y);
  ColorRGBA GetColor();

protected:
  SDL_Texture *mButtonTexture;
  ColorRGBA mButtonColor;
};