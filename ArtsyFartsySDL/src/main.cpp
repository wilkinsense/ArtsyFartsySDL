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

class TestClass
{
public:
  void ChangeInstrument()
  {
    printf("Changed instrument.\n");

    InstrumentManager *im = InstrumentManager::GetInstance();
    im->SetBrushType((BrushType)((im->GetBrushType() + 1) % BRUSHTYPE_COUNT));
  }

  void ShowReplay()
  {
    ScreenManager *sm = ScreenManager::GetInstance();
    sm->ShowScreen("REPLAY");
  }

  void FingerMotion()
  {
    printf("FUUUUUUUCK\n");
  }
};

int main(int argc, char ** argv)
{
  TestClass c;
  InputManager::GetInstance()->AssignEvent(SDL_KEYDOWN, &c, (InputMemberEvent)(&TestClass::ShowReplay));

  InputManager::GetInstance()->AssignEvent(SDL_FINGERMOTION, &c, (InputMemberEvent)(&TestClass::FingerMotion));

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