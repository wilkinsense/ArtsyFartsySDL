#include "ReplayScreen.h"
#include "../Instrument.h"
#include "../Instruments\Pencil.h"
#include "../Instruments\Confetti.h"
#include "../InstrumentTypes.h"
#include "../InstrumentManager.h"
#include <vector>
#include "../Shape.h"

ReplayScreen::ReplayScreen()
{
  mInstruments.insert(std::pair<int, Instrument *>(BRUSHTYPE_PENCIL, new Pencil()));
  mInstruments.insert(std::pair<int, Instrument *>(BRUSHTYPE_CONFETTI, new Confetti()));
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

    currentShape->drawn = false;
  }
}

void ReplayScreen::Update(const SDL_EventType &type)
{

}

void ReplayScreen::Draw(SDL_Renderer *renderer)
{
  Instrument *currentInstrument = nullptr;

  const std::vector<Shape *>* shapes = InstrumentManager::GetInstance()->GetActiveShapes();
  for (auto shapeItr = shapes->begin(); shapeItr != shapes->end(); shapeItr++)
  {
    Shape *currentShape = (*shapeItr);
    if (currentShape->drawn == false)
    {
      auto instrumentItr = mInstruments.find(currentShape->brushType);
      if (instrumentItr != mInstruments.end())
      {
        currentInstrument = instrumentItr->second;
        bool didDraw = currentInstrument->DrawShape(renderer, currentShape, true);
        if (didDraw)
        {
          break;
        }
        else
        {
          currentShape->drawn = true;
        }
      }
    }
  }
}