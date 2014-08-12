#pragma once

#include <SDL.h>
#include <vector>
#include "ColorHelper.h"
#include "InstrumentTypes.h"

struct ShapeBlock
{
  Uint32 timestamp;
  unsigned int x;
  unsigned int y;
  int brushSize;
  //BrushType brushType;
  ColorRGBA brushColor;
  bool drawn;

  ShapeBlock() : drawn(false) {}
};

class Shape
{
public:
  Shape();

  void AddBlock(const ShapeBlock &block);
  const std::vector<ShapeBlock *>* GetBlocks();

  bool drawn;
  BrushType brushType;

protected:
  std::vector<ShapeBlock *> mBlocks;
};