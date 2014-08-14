#include "DrawScreen.h"
#include "InputManager.h"
#include "InstrumentWrapper.h"
#include "Shape.h"
#include <SDL2_gfxPrimitives.h>
#include "Instrument.h"
#include "Instruments\Pencil.h"
#include "Instruments\Confetti.h"

DrawScreen::DrawScreen()
{
  mInstruments.insert(std::pair<int, Instrument *>(BRUSHTYPE_PENCIL, new Pencil()));
  mInstruments.insert(std::pair<int, Instrument *>(BRUSHTYPE_CONFETTI, new Confetti()));
}

DrawScreen::~DrawScreen()
{
  for (auto mapItr = mInstruments.begin(); mapItr != mInstruments.end(); mapItr++)
  {
    Instrument *instrument = mapItr->second;
    delete instrument;
  }

  mInstruments.clear();
}

void DrawScreen::OnEnter()
{
  InputManager::GetInstance()->AssignEvent(SDL_MOUSEBUTTONDOWN, (InputEvent)(&InstrumentWrapper::InputBegan));
}

void DrawScreen::OnExit()
{
  InputManager::GetInstance()->RemoveEvent(SDL_MOUSEBUTTONDOWN, (InputEvent)(&InstrumentWrapper::InputBegan));
  InputManager::GetInstance()->RemoveEvent(SDL_MOUSEMOTION, (InputEvent)(&InstrumentWrapper::InputMoved));
  InputManager::GetInstance()->RemoveEvent(SDL_MOUSEBUTTONUP, (InputEvent)(&InstrumentWrapper::InputEnded));
}

void DrawScreen::Update(const SDL_EventType &type)
{
  InputManager::GetInstance()->ProcessEvent(type);
}

void DrawScreen::Draw(SDL_Renderer *renderer)
{
  const float adjustment = 1.0001f;
  static float modifier = 1.0f;
  if (modifier > 1.0f)
  {
    modifier *= 0.99f;
    if (modifier < 1.0f)
    {
      modifier = 1.0f;
    }
  }
  //printf("Modifier: %f\n", modifier);

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
        currentInstrument->DrawShape(renderer, currentShape);
      }
    }
  }
}