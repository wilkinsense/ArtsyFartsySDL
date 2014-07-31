#pragma once
#include <SDL_events.h>
#include "ColorHelper.h"
#include "InstrumentTypes.h"

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

  void      InputBegan();
  void      InputMoved();
  void      InputEnded();

private:
  static InstrumentManager *kInstance;
  InstrumentManager();

  BrushType mBrushType;
  int       mBrushSize;
  ColorRGBA mBrushColor;

  SDL_EventType mInstrumentState;
};