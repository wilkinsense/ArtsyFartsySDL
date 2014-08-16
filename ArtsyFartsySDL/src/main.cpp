#include <SDL.h>
#include <stdio.h>
#include <iostream>
#include <AK\SoundEngine\Common\AkSoundEngine.h>
#include "InputManager.h"
#include "InstrumentWrapper.h"
#include "HistoryManager.h"
#include <gl\GL.h>
#include <gl\GLU.h>
#include <SDL2_gfxPrimitives.h>
#include "ScreenManager.h"
#include "DrawScreen.h"
#include "Screens\ReplayScreen.h"

#define MAX_BRUSH_SIZE 20
#define MIN_BRUSH_SIZE 2

class TestClass
{
public:
  void InputDispatch(SDL_Event e);
  void ChangeInstrument();
  void ShowReplay();

  void IncreaseBrushSize();
  void DecreaseBrushize();
};

int main(int argc, char ** argv)
{
  TestClass c;
  InputManager::GetInstance()->AssignEvent(SDL_KEYDOWN, &c, (InputMemberEvent)(&TestClass::InputDispatch));

  DrawScreen draw;
  ReplayScreen replay;

  ScreenManager *screenManager = ScreenManager::GetInstance();
  screenManager->PushScreen("DRAW", &draw);
  screenManager->PushScreen("REPLAY", &replay);

  screenManager->ShowScreen("DRAW");

  while (screenManager->IsRunning())
  {
    screenManager->Update();
    screenManager->Draw();
  }

  ScreenManager::DestroyInstance();
  
  return 0;
}


void TestClass::InputDispatch(SDL_Event e)
{
  SDL_KeyboardEvent ke = e.key;
  SDL_Keycode kc = ke.keysym.sym;
  switch (kc)
  {
  case SDLK_SPACE:
    ShowReplay();
    break;

  case SDLK_q:
    ChangeInstrument();
    break;

  case SDLK_z:
    DecreaseBrushize();
    break;

  case SDLK_x:
    IncreaseBrushSize();
    break;
  }
}

void TestClass::ChangeInstrument()
{
  printf("Changed instrument.\n");

  InstrumentManager *im = InstrumentManager::GetInstance();
  im->SetBrushType((BrushType)((im->GetBrushType() + 1) % BRUSHTYPE_COUNT));
}

void TestClass::ShowReplay()
{
  ScreenManager *sm = ScreenManager::GetInstance();
  sm->ShowScreen("REPLAY");
}

void TestClass::IncreaseBrushSize()
{
  InstrumentManager *im = InstrumentManager::GetInstance();
  int brushSize = im->GetBrushSize() + 1;
  if (brushSize > MAX_BRUSH_SIZE)
  {
    brushSize = MAX_BRUSH_SIZE;
  }

  im->SetBrushSize(brushSize);
}

void TestClass::DecreaseBrushize()
{
  InstrumentManager *im = InstrumentManager::GetInstance();
  int brushSize = im->GetBrushSize() - 1;
  if (brushSize < MIN_BRUSH_SIZE)
  {
    brushSize = MIN_BRUSH_SIZE;
  }

  im->SetBrushSize(brushSize);
}