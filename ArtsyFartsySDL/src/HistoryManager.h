#pragma once

#include "ColorHelper.h"
#include "Instruments/InstrumentTypes.h"
#include "Shape.h"
#include <vector>

class HistoryManager
{
public:
    static HistoryManager* GetInstance();
    void SetRandomSeed(uint32_t randomSeed);
    uint32_t GetRandomSeed();

protected:
    static HistoryManager* kInstance;
    uint32_t mRandomSeed;
};
