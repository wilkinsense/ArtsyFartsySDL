#include "DrawScreen.h"
#include "InputManager.h"
#include "InstrumentWrapper.h"
#include "Shape.h"
#include <SDL2_gfxPrimitives.h>
#include "Instrument.h"
#include "Instruments\Pencil.h"
#include "Instruments\Confetti.h"
#include "Buttons\ColourButton.h"
#include <SDL_image.h>
#include "ScreenManager.h"

#define MAX_X 30

DrawScreen::DrawScreen()
{
  mInstruments.insert(std::pair<int, Instrument *>(BRUSHTYPE_PENCIL, new Pencil()));
  mInstruments.insert(std::pair<int, Instrument *>(BRUSHTYPE_CONFETTI, new Confetti()));

  int result = IMG_Init(IMG_INIT_PNG);
  if (result & IMG_INIT_PNG)
  {
    SDL_Surface *buttonSurface = IMG_Load("res/button.png");
    mButtonTexture = SDL_CreateTextureFromSurface(ScreenManager::GetInstance()->GetRenderer(), buttonSurface);
  }

  mButtons.push_back(new ColourButton(mButtonTexture, ColorRGBA(0xFF, 0x0, 0x00, 0xFF))); // red
  mButtons.push_back(new ColourButton(mButtonTexture, ColorRGBA(0xFF, 0xFF, 0x00, 0xFF))); // yellow
  mButtons.push_back(new ColourButton(mButtonTexture, ColorRGBA(0xFF, 0x0, 0xFF, 0xFF))); // purple
  mButtons.push_back(new ColourButton(mButtonTexture, ColorRGBA(0x00, 0x0, 0xFF, 0xFF))); // blue
  mButtons.push_back(new ColourButton(mButtonTexture, ColorRGBA(0x00, 0xFF, 0x00, 0xFF))); // green
}

DrawScreen::~DrawScreen()
{
  for (auto mapItr = mInstruments.begin(); mapItr != mInstruments.end(); mapItr++)
  {
    Instrument *instrument = mapItr->second;
    delete instrument;
  }

  for (auto buttonItr = mButtons.begin(); buttonItr != mButtons.end(); buttonItr++)
  {
    ColourButton *button = *buttonItr;
    delete button;
  }

  mInstruments.clear();
  mButtons.clear();
}

void DrawScreen::OnEnter()
{
  //InputManager::GetInstance()->AssignEvent(SDL_MOUSEBUTTONDOWN, (InputEvent)(&InstrumentWrapper::InputBegan));
  InputManager::GetInstance()->AssignEvent(SDL_MOUSEBUTTONDOWN, this, (InputMemberEvent)(&DrawScreen::CheckInput));

  mButtonsX = -30;
  mButtonsY = 30;

  mButtonsOffsetX = 0;
  mButtonsOffsetY = 65;
}

void DrawScreen::OnExit()
{
  //InputManager::GetInstance()->RemoveEvent(SDL_MOUSEBUTTONDOWN, (InputEvent)(&InstrumentWrapper::InputBegan));
  InputManager::GetInstance()->RemoveEvent(SDL_MOUSEMOTION, (InputEvent)(&InstrumentWrapper::InputMoved));
  InputManager::GetInstance()->RemoveEvent(SDL_MOUSEBUTTONUP, (InputEvent)(&InstrumentWrapper::InputEnded));
}

void DrawScreen::Update(const SDL_Event &e)
{
  if (mButtonsX < MAX_X)
  {
    //mButtonsX += 1;
  }

  InputManager::GetInstance()->ProcessEvent(e);
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

  int xPos = mButtonsX;
  int yPos = mButtonsY;
  for (int buttonIndex = 0; buttonIndex < mButtons.size(); buttonIndex++)
  {
    mButtons[buttonIndex]->Draw(renderer, xPos, yPos);
    xPos += mButtonsOffsetX;
    yPos += mButtonsOffsetY;
  }
}

void DrawScreen::CheckInput(SDL_Event e)
{
  int x = e.button.x;
  int y = e.button.y;

  int halfWidth = 30;
  int xPos = mButtonsX + halfWidth, yPos = mButtonsY + halfWidth;

  bool foundInput = false;
  ColorRGBA color;
  for (int buttonIndex = 0; buttonIndex < mButtons.size(); buttonIndex++)
  {
    int diffX = abs(x - xPos);
    int diffY = abs(y - yPos);
    float diff = sqrtf((diffX * diffX) + (diffY * diffY));
    if (diff <= halfWidth)
    {
      foundInput = true;
      color = mButtons[buttonIndex]->GetColor();
      break;
    }

    xPos += mButtonsOffsetX;
    yPos += mButtonsOffsetY;
  }

  if (foundInput)
  {
    printf("Changing colours!");
    InstrumentManager::GetInstance()->SetBrushColor(color);
  }
  else
  {
    InstrumentWrapper::InputBegan(e);
  }
}
