#pragma once

#include <vector>
#include "ColorHelper.h"
#include "InstrumentTypes.h"
#include "Shape.h"

class HistoryManager
{
public:
  static HistoryManager* GetInstance();

protected:
  static HistoryManager *kInstance;
};
