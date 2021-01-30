#pragma once

#include "Screen.h"
#include "../Instruments/Instrument.h"
#include <map>
#include <SDL_types.h>

enum class BrushType;
class Shape;

class ReplayScreen : public Screen
{
public:
    ReplayScreen();
    ~ReplayScreen();

    void OnEnter();

    void Update(const SDL_Event& e);
    void Draw(SDL_Renderer* renderer);

protected:
    std::map<BrushType, Instrument*> mInstruments;

    Uint32 mLastTimestamp;
    Uint32 mCurrentTimestamp;

    Uint16 mShapeIndex;
    Uint32 mBlockIndex;
};
