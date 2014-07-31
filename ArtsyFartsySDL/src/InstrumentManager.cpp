#include "InstrumentManager.h"
#include <iostream>

InstrumentManager* InstrumentManager::kInstance = NULL;

InstrumentManager* InstrumentManager::GetInstance()
{
  if (kInstance == nullptr)
  {
    kInstance = new InstrumentManager();
  }

  return kInstance;
}

void InstrumentManager::DestroyInstance()
{
  if (kInstance != nullptr)
  {
    delete kInstance;
    kInstance = nullptr;
  }
}

InstrumentManager::InstrumentManager() :
mBrushSize(0), 
mBrushType(BRUSHTYPE_PENCIL),
mBrushColor(ColorHelper::ColorFromRGBA(0, 0, 0, 0)),
mInstrumentState(SDL_MOUSEBUTTONUP)
{

}

int InstrumentManager::GetBrushSize()
{
  return mBrushSize;
}

BrushType InstrumentManager::GetBrushType()
{
  return mBrushType;
}

ColorRGBA InstrumentManager::GetBrushColor()
{
  return mBrushColor;
}

void InstrumentManager::SetBrushSize(int size)
{
  mBrushSize = size;
}

void InstrumentManager::SetBrushType(BrushType type)
{
  mBrushType = type;
}

void InstrumentManager::SetBrushColor(ColorRGBA color)
{
  mBrushColor = color;
}

void InstrumentManager::InputBegan()
{
  mInstrumentState = SDL_MOUSEBUTTONDOWN;
  printf("Mouse down!\n");
}

void InstrumentManager::InputMoved()
{
  printf("Mouse moved!\n");
}

void InstrumentManager::InputEnded()
{
  mInstrumentState = SDL_MOUSEBUTTONUP;
  printf("Mouse up!\n");
}