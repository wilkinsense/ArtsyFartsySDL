#include "HistoryManager.h"
#include <time.h>

HistoryManager* HistoryManager::kInstance = nullptr;

HistoryManager* HistoryManager::GetInstance()
{
  if (kInstance == nullptr)
  {
    kInstance = new HistoryManager();
  }

  return kInstance;
}

void HistoryManager::AddBlock(unsigned int x, unsigned int y, ColorRGBA color, BrushType type, int size)
{
  HistoryBlock *newBlock = new HistoryBlock();
  mActiveBlocks.push_back(newBlock);

  newBlock->timestamp = time(0);
  newBlock->pos = (x << 4) | y;
  newBlock->x = x;
  newBlock->y = y;
  newBlock->brushColor = color;
  newBlock->brushType = type;
  newBlock->brushSize = size;
}

const std::vector<HistoryBlock *>* HistoryManager::GetActiveBlocks()
{
  return &mActiveBlocks;
}
