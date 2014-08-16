#include "DrawScreen.h"
#include "InputManager.h"
#include "InstrumentWrapper.h"
#include "Shape.h"
#include <SDL2_gfxPrimitives.h>
#include "Instrument.h"
#include "Instruments\Pencil.h"
#include "Instruments\Confetti.h"
#include "Instruments\Spray.h"
#include "Buttons\ColourButton.h"
#include <SDL_image.h>
#include "ScreenManager.h"

#define MAX_X 0
#define MIN_X -30

DrawScreen::DrawScreen()
{
  mInstruments.insert(std::pair<int, Instrument *>(BRUSHTYPE_PENCIL, new Pencil()));
  mInstruments.insert(std::pair<int, Instrument *>(BRUSHTYPE_CONFETTI, new Confetti()));
  mInstruments.insert(std::pair<int, Instrument *>(BRUSHTYPE_SPRAY, new Spray()));

  SDL_Window *window = ScreenManager::GetInstance()->GetWindow();
  SDL_Renderer *renderer = ScreenManager::GetInstance()->GetRenderer();

  int result = IMG_Init(IMG_INIT_PNG);
  if (result & IMG_INIT_PNG)
  {
    SDL_Surface *buttonSurface = IMG_Load("res/button.png");
    mButtonTexture = SDL_CreateTextureFromSurface(renderer, buttonSurface);
  }

  int width, height;
  SDL_GetWindowSize(window, &width, &height);
  mBackBuffer = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, width, height);
  
  SDL_Texture *oldTexture = SDL_GetRenderTarget(renderer);
  int success = SDL_SetRenderTarget(renderer, mBackBuffer);

  SDL_SetRenderDrawColor(renderer, 0xff, 0xff, 0xff, 0xff);
  SDL_RenderClear(renderer);

  SDL_SetRenderTarget(renderer, oldTexture);

  mButtons.push_back(new ColourButton(mButtonTexture, ColorRGBA(0xFF, 0x0, 0x00, 0xFF), mButtonsX, mButtonsY)); // red
  mButtons.push_back(new ColourButton(mButtonTexture, ColorRGBA(0xFF, 0xFF, 0x00, 0xFF), mButtonsX, mButtonsY)); // yellow
  mButtons.push_back(new ColourButton(mButtonTexture, ColorRGBA(0xFF, 0x0, 0xFF, 0xFF), mButtonsX, mButtonsY)); // purple
  mButtons.push_back(new ColourButton(mButtonTexture, ColorRGBA(0x00, 0x0, 0xFF, 0xFF), mButtonsX, mButtonsY)); // blue
  mButtons.push_back(new ColourButton(mButtonTexture, ColorRGBA(0x00, 0xFF, 0x00, 0xFF), mButtonsX, mButtonsY)); // green
  mButtons.push_back(new ColourButton(mButtonTexture, ColorRGBA(0x80, 0x40, 0x00, 0xFF), mButtonsX, mButtonsY)); // brown
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
  InputManager::GetInstance()->AssignEvent(SDL_MOUSEBUTTONDOWN, this, (InputMemberEvent)(&DrawScreen::CheckInput));
  InputManager::GetInstance()->AssignEvent(SDL_MOUSEMOTION, this, (InputMemberEvent)(&DrawScreen::CheckInput));
  InputManager::GetInstance()->AssignEvent(SDL_MOUSEBUTTONUP, this, (InputMemberEvent)(&DrawScreen::CheckInput));

  mButtonsX = MIN_X;
  mButtonsY = 30;

  mButtonsOffsetX = 0;
  mButtonsOffsetY = 65;

  mWithinButtons = false;
}

void DrawScreen::OnExit()
{
  InputManager::GetInstance()->RemoveEvent(SDL_MOUSEMOTION, (InputEvent)(&InstrumentWrapper::InputMoved));
  InputManager::GetInstance()->RemoveEvent(SDL_MOUSEBUTTONUP, (InputEvent)(&InstrumentWrapper::InputEnded));

  InputManager::GetInstance()->RemoveEvent(SDL_MOUSEBUTTONDOWN, this, (InputMemberEvent)(&DrawScreen::CheckInput));
  InputManager::GetInstance()->RemoveEvent(SDL_MOUSEMOTION, this, (InputMemberEvent)(&DrawScreen::CheckInput));
  InputManager::GetInstance()->RemoveEvent(SDL_MOUSEBUTTONUP, this, (InputMemberEvent)(&DrawScreen::CheckInput));

}

void DrawScreen::Update(const SDL_Event &e)
{
  if (mWithinButtons)
  {
    if (mButtonsX < MAX_X)
    {
      mButtonsX++;
      if (mButtonsX >= MAX_X)
      {
        mButtonsX = MAX_X;
      }
    }
  }
  else if (mButtonsX > MIN_X)
  {
    mButtonsX--;
    if (mButtonsX <= MIN_X)
    {
      mButtonsX = MIN_X;
    }
  }

  int xPos = mButtonsX, yPos = mButtonsY;
  for (auto buttonItr = mButtons.begin(); buttonItr != mButtons.end(); buttonItr++)
  {
    ColourButton *button = *buttonItr;
    button->SetX(xPos);
    button->SetY(yPos);

    xPos += mButtonsOffsetX;
    yPos += mButtonsOffsetY;
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

  SDL_Texture *oldTarget = SDL_GetRenderTarget(renderer);
  int success = SDL_SetRenderTarget(renderer, mBackBuffer);

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

  SDL_SetRenderTarget(renderer, oldTarget);
  SDL_RenderClear(renderer);

  SDL_RenderCopy(renderer, mBackBuffer, NULL, NULL);

  for (auto buttonItr = mButtons.begin(); buttonItr != mButtons.end(); buttonItr++)
  {
    ColourButton *button = *buttonItr;
    button->Draw(renderer);
  }
}

void DrawScreen::CheckInput(SDL_Event e)
{
  int x = e.button.x;
  int y = e.button.y;
  ColourButton *button = nullptr;

  if (e.type == SDL_MOUSEBUTTONDOWN)
  {
    if (IsWithinButton(x, y, &button))
    {
      printf("Changing colours!");
      ColorRGBA color = button->GetColor();
      InstrumentManager::GetInstance()->SetBrushColor(color);
    }
    else
    {
      InputManager::GetInstance()->RemoveEvent(SDL_MOUSEMOTION, this, (InputMemberEvent)(&DrawScreen::CheckInput));
      InstrumentWrapper::InputBegan(e);
    }
  }
  else if (e.type == SDL_MOUSEMOTION)
  {
    mWithinButtons = IsWithinButton(x, y, &button);
  }
  else if (e.type == SDL_MOUSEBUTTONUP)
  {
    InputManager::GetInstance()->AssignEvent(SDL_MOUSEMOTION, this, (InputMemberEvent)(&DrawScreen::CheckInput));
  }
}

bool DrawScreen::IsWithinButton(int x, int y, ColourButton **button)
{
  int xPos = mButtonsX, yPos = mButtonsY;
  int halfWidth = 30;

  bool foundInput = false;
  for (auto buttonItr = mButtons.begin(); buttonItr != mButtons.end(); buttonItr++)
  {
    int diffX = abs(x - xPos - halfWidth);
    int diffY = abs(y - yPos - halfWidth);
    float diff = sqrtf((diffX * diffX) + (diffY * diffY));
    if (diff <= halfWidth)
    {
      foundInput = true;
      if (button != nullptr)
      {
        *button = (*buttonItr);
      }
      break;
    }

    xPos += mButtonsOffsetX;
    yPos += mButtonsOffsetY;
  }

  return foundInput;
}
