#include "Shape.h"

Shape::Shape()
{
  drawn = false;
}

void Shape::AddBlock(const ShapeBlock &block)
{
  ShapeBlock *shapeBlock = new ShapeBlock(block);
  mBlocks.push_back(shapeBlock);
}

const std::vector<ShapeBlock *>* Shape::GetBlocks()
{
  return &mBlocks;
}