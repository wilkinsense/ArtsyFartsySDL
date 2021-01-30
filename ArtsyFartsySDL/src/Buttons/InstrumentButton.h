#pragma once
#include "SelectableButton.h"
#include "../ColorHelper.h"

struct SDL_Texture;
struct SDL_Renderer;

class InstrumentButton : public SelectableButton
{
public:
    InstrumentButton(SDL_Texture* buttonTexture, int x, int y);

    void Draw(SDL_Renderer* renderer);

protected:
};