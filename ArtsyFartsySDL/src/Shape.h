#pragma once

#include <vector>
#include "ColorHelper.h"

struct ShapeBlock
{
  long timestamp;
  unsigned int x;
  unsigned int y;
  int brushSize;
  int brushType;
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

protected:
  std::vector<ShapeBlock *> mBlocks;
};