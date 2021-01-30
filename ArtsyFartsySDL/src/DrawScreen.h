#pragma once

#include "Screens\Screen.h"
#include <map>
#include <vector>

class ColourButton;
class Instrument;
class InstrumentButton;
struct SDL_Texture;

class DrawScreen : public Screen
{
public:
    DrawScreen();
    ~DrawScreen();

    void OnEnter();
    void OnExit();

    void Update(const SDL_Event& e);
    void Draw(SDL_Renderer* renderer);

    void Clear();

protected:
    std::map<int, Instrument*> mInstruments;

    SDL_Texture* mButtonTexture;
    SDL_Texture* mPencilTexture;
    SDL_Texture* mSprayTexture;
    SDL_Texture* mConfettiTexture;
    SDL_Texture* mEraserTexture;

    std::vector<ColourButton*> mButtons;
    InstrumentButton* mPencilButton;
    InstrumentButton* mSprayButton;
    std::map<int, InstrumentButton*> mInstrumentButtons;

    void CheckInput(SDL_Event e);
    bool IsWithinButton(int x, int y, ColourButton** button);

    int mButtonsX, mButtonsY;
    int mButtonsOffsetX, mButtonsOffsetY;
    bool mWithinButtons;

    SDL_Texture* mBackBuffer;
};