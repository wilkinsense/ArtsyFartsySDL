#pragma once

#include "InstrumentTypes.h"
#include "../ColorHelper.h"
#include <SDL_events.h>
#include <time.h>
#include <vector>

class Shape;

class InstrumentManager
{
public:
    static InstrumentManager* GetInstance();
    static void DestroyInstance();

    int       GetBrushSize();
    BrushType GetBrushType();
    ColorRGBA GetBrushColor();
    void      SetBrushSize(int size);
    void      SetBrushType(BrushType type);
    void      SetBrushColor(ColorRGBA color);

    void      InputBegan(SDL_Event e);
    void      InputMoved(SDL_Event e);
    void      InputEnded(SDL_Event e);

    const std::vector<Shape*>* GetActiveShapes();

    void ClearAllShapes();

private:
    static InstrumentManager* kInstance;
    InstrumentManager();

    BrushType mBrushType;
    int       mBrushSize;
    ColorRGBA mBrushColor;

    std::vector<Shape*> mShapes;
    Shape* currentShape;

    void GetCurrentInput(SDL_Event e);

    SDL_EventType mInstrumentState;
};