#include "ReplayScreen.h"
#include "../Instrument.h"
#include "../Instruments\Pencil.h"
#include "../Instruments\Confetti.h"
#include "../Instruments/Spray.h"
#include "../Instruments/Eraser.h"
#include "../InstrumentTypes.h"
#include "../InstrumentManager.h"
#include <vector>
#include "../Shape.h"
#include "../InputManager.h"
#include "../ScreenManager.h"

ReplayScreen::ReplayScreen()
{
  mInstruments.insert(std::pair<int, Instrument *>(BRUSHTYPE_PENCIL, new Pencil()));
  mInstruments.insert(std::pair<int, Instrument *>(BRUSHTYPE_CONFETTI, new Confetti()));
  mInstruments.insert(std::pair<int, Instrument *>(BRUSHTYPE_SPRAY, new Spray()));
  mInstruments.insert(std::pair<int, Instrument *>(BRUSHTYPE_ERASER, new Eraser()));
}

ReplayScreen::~ReplayScreen()
{
  for (auto mapItr = mInstruments.begin(); mapItr != mInstruments.end(); mapItr++)
  {
    Instrument *instrument = mapItr->second;
    delete instrument;
  }

  mInstruments.clear();
}

void ReplayScreen::OnEnter()
{
  const std::vector<Shape *>* shapes = InstrumentManager::GetInstance()->GetActiveShapes();
  for (auto shapeItr = shapes->begin(); shapeItr != shapes->end(); shapeItr++)
  {
    Shape *currentShape = (*shapeItr);
    auto blocks = currentShape->GetBlocks();
    for (auto blockItr = blocks->begin(); blockItr != blocks->end(); blockItr++)
    {
      (*blockItr)->drawn = false;
    }
  }

  mShapeIndex = 0;
  mBlockIndex = 0;

  mLastTimestamp = SDL_GetTicks();

  /* Clear the screen. */
  ScreenManager::GetInstance()->ClearRenderer();
}

void ReplayScreen::Update(const SDL_Event &e)
{
  InputManager::GetInstance()->ProcessEvent(e);
}

void ReplayScreen::Draw(SDL_Renderer *renderer)
{
  Instrument *currentInstrument = nullptr;
  bool willDraw = false;

  mCurrentTimestamp = SDL_GetTicks();

  const std::vector<Shape *>* shapes = InstrumentManager::GetInstance()->GetActiveShapes();
  if (shapes->size() > mShapeIndex)
  {
    Shape *currentShape = shapes->at(mShapeIndex);
    auto blocks = currentShape->GetBlocks();

    if (mBlockIndex < blocks->size())
    {
      ShapeBlock *firstBlock = blocks->at(mBlockIndex);
      if (mBlockIndex + 1 < blocks->size())
      {
        ShapeBlock *secondBlock = blocks->at(mBlockIndex + 1);

        Uint32 blockTimeDiff = (Uint32)((secondBlock->timestamp - firstBlock->timestamp) * 1.25f);
        Uint32 incrementalTimeDiff = mCurrentTimestamp - mLastTimestamp;

        if (incrementalTimeDiff >= blockTimeDiff)
        {
          willDraw = true;
          mLastTimestamp = mCurrentTimestamp;
        }
      }
      if (blocks->size() == 1)
      {
        willDraw = true;
      }
    }

    if (willDraw)
    {
      auto instrumentItr = mInstruments.find(currentShape->brushType);
      if (instrumentItr != mInstruments.end())
      {
        currentInstrument = instrumentItr->second;
        currentInstrument->DrawShape(renderer, currentShape, true);

        mBlockIndex++;
        if (mBlockIndex + 1 >= blocks->size())
        {
          mShapeIndex++;
          mBlockIndex = 0;
        }
      }
    }
  }
}