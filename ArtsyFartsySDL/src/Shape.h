#pragma once

#include "ColorHelper.h"
#include "Instruments/InstrumentTypes.h"
#include <SDL.h>
#include <vector>

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

    void AddBlock(const ShapeBlock& block);
    const std::vector<ShapeBlock*>* GetBlocks();
    void Clear();

    bool drawn;
    BrushType brushType;

protected:
    std::vector<ShapeBlock*> mBlocks;
};