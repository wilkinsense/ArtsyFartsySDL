#pragma once

#include <vector>

struct ShapeBlock
{
  long timestamp;
  unsigned int x;
  unsigned int y;
  int brushSize;
  int brushType;
  int brushColor;
};

class Shape
{
public:
  void AddBlock(ShapeBlock &block);
  std::vector<ShapeBlock *>* GetBlocks();

protected:
  std::vector<ShapeBlock *> mBlocks;
};