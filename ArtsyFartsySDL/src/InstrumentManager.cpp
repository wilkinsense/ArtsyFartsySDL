#include "InstrumentManager.h"
#include "HistoryManager.h"
#include <iostream>
#include "Shape.h"

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
  int x, y;
  SDL_GetMouseState(&x, &y);
  printf("Mouse moved at: %d, %d\n", x, y);
  HistoryManager::GetInstance()->AddBlock(x, y, ColorHelper::ColorFromRGBA(0x00, 0xFF, 0x00, 0xFF), mBrushType, mBrushSize);
}

void InstrumentManager::InputEnded()
{
  mInstrumentState = SDL_MOUSEBUTTONUP;
  printf("Mouse up!\n");
}