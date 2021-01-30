#include "Shape.h"

Shape::Shape()
{
    drawn = false;
}

void Shape::AddBlock(const ShapeBlock& block)
{
    ShapeBlock* shapeBlock = new ShapeBlock(block);
    mBlocks.push_back(shapeBlock);
}

const std::vector<ShapeBlock*>* Shape::GetBlocks()
{
    return &mBlocks;
}

void Shape::Clear()
{
    for (auto blocks = mBlocks.begin(); blocks != mBlocks.end(); blocks++)
    {
        ShapeBlock* block = (*blocks);
        delete block;
    }

    mBlocks.clear();
}
