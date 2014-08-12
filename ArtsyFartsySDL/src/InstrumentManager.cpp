#include "InstrumentManager.h"
#include "HistoryManager.h"
#include <iostream>
#include "Shape.h"
#include <SDL.h>

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
mBrushSize(5), 
mBrushType(BRUSHTYPE_PENCIL),
mBrushColor(ColorRGBA(0x00, 0xFF, 0x00, 0xFF)),
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

  Shape *newShape = new Shape();
  mShapes.push_back(newShape);

  currentShape = newShape;
  currentShape->brushType = mBrushType;

  mBrushColor = ColorRGBA(rand() % 255, rand() % 255, rand() % 255, 255);
  GetCurrentInput();
}

void InstrumentManager::InputMoved()
{
  int x, y;
  SDL_GetMouseState(&x, &y);
  printf("Mouse moved at: %d, %d\n", x, y);

  GetCurrentInput();
}

void InstrumentManager::InputEnded()
{
  mInstrumentState = SDL_MOUSEBUTTONUP;
  printf("Mouse up!\n");

  currentShape->drawn = true;
}

const std::vector<Shape *>* InstrumentManager::GetActiveShapes()
{
  return &mShapes;
}

void InstrumentManager::GetCurrentInput()
{
  int x, y;
  SDL_GetMouseState(&x, &y);

  ShapeBlock currentBlock;
  currentBlock.x = x;
  currentBlock.y = y;
  currentBlock.brushColor = mBrushColor;
  currentBlock.timestamp = SDL_GetTicks();
  currentBlock.brushSize = mBrushSize;

  currentShape->AddBlock(currentBlock);
}

void InstrumentManager::DrawShapes(BrushType type)
{
  
}
