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

void HistoryManager::SetRandomSeed(uint32_t randomSeed)
{
    srand(randomSeed);
    mRandomSeed = randomSeed;
}

uint32_t HistoryManager::GetRandomSeed()
{
    return mRandomSeed;
}
