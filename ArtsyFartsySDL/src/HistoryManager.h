#pragma once

#include "ColorHelper.h"
#include "InstrumentTypes.h"
#include "Shape.h"
#include <vector>

class HistoryManager
{
public:
    static HistoryManager* GetInstance();

protected:
    static HistoryManager* kInstance;
};
