#pragma once

#include "Screen.h"
#include <map>
#include <vector>

enum class BrushType;
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
    std::map<BrushType, Instrument*> mInstruments;

    SDL_Texture* mButtonTexture;
    SDL_Texture* mPencilTexture;
    SDL_Texture* mSprayTexture;
    SDL_Texture* mConfettiTexture;
    SDL_Texture* mEraserTexture;

    std::vector<ColourButton*> mButtons;
    InstrumentButton* mPencilButton;
    InstrumentButton* mSprayButton;
    std::map<BrushType, InstrumentButton*> mInstrumentButtons;

    void CheckInput(SDL_Event e);
    bool IsWithinButton(int32_t x, int32_t y, ColourButton** button);

    int32_t mButtonsX = 0, mButtonsY = 0;
    int32_t mButtonsOffsetX = 0, mButtonsOffsetY = 0;
    bool mWithinButtons = false;

    SDL_Texture* mBackBuffer = nullptr;
};