#pragma once
#include "../ColorHelper.h"

struct SDL_Texture;
struct SDL_Renderer;

class SelectableButton
{
public:
    SelectableButton(SDL_Texture* buttonTexture, int x, int y);

    virtual void Draw(SDL_Renderer* renderer) = 0;

    void SetX(int x);
    void SetY(int y);

    bool IsPointWithinButton(int x, int y);

protected:
    int mPositionX;
    int mPositionY;

    SDL_Texture* mButtonTexture;
};