#pragma once

#include <vector>
#include "ColorHelper.h"
#include "InstrumentTypes.h"

struct HistoryBlock
{
  long timestamp;
  unsigned int pos;
  int brushSize;
  int brushType;
  int brushColor;
};

class HistoryManager
{
public:
  static HistoryManager* GetInstance();
  void AddBlock(unsigned int x, unsigned int y, ColorRGBA color, BrushType type, int size);

protected:
  static HistoryManager *kInstance;

  std::vector<HistoryBlock *> mActiveBlocks;
};
