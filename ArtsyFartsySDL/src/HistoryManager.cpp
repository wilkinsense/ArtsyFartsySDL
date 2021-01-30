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
