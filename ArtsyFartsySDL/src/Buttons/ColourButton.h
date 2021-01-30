#pragma once
#include "SelectableButton.h"
#include "../ColorHelper.h"

struct SDL_Texture;
struct SDL_Renderer;

class ColourButton : public SelectableButton
{
public:
    ColourButton(SDL_Texture* buttonTexture, ColorRGBA color, int x, int y);

    void Draw(SDL_Renderer* renderer);
    ColorRGBA GetColor();

protected:
    ColorRGBA mButtonColor;
};