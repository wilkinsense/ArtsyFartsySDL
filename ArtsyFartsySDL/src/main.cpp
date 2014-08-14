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

class TestClass
{
public:
  void CallAThing()
  {
    printf("Thing is called.\n");
    InputManager::GetInstance()->RemoveEvent(SDL_KEYDOWN, this, (InputMemberEvent)&TestClass::CallAThing);
    InputManager::GetInstance()->AssignEvent(SDL_KEYDOWN, this, (InputMemberEvent)&TestClass::CallAnotherThing);

    InstrumentManager *im = InstrumentManager::GetInstance();
    im->SetBrushType((BrushType)((im->GetBrushType() + 1) % BRUSHTYPE_COUNT));
  }

  void CallAnotherThing()
  {
    printf("This other thing is called.\n");
    InputManager::GetInstance()->RemoveEvent(SDL_KEYDOWN, this, (InputMemberEvent)&TestClass::CallAnotherThing);
    InputManager::GetInstance()->AssignEvent(SDL_KEYDOWN, this, (InputMemberEvent)&TestClass::CallAThing);
    
    InstrumentManager *im = InstrumentManager::GetInstance();
    im->SetBrushType((BrushType)((im->GetBrushType() + 1) % BRUSHTYPE_COUNT));
  }
};

int main(int argc, char ** argv)
{
  TestClass c;
  InputManager::GetInstance()->AssignEvent(SDL_KEYDOWN, &c, (InputMemberEvent)(&TestClass::CallAThing));

  DrawScreen draw;
  ScreenManager *screenManager = ScreenManager::GetInstance();
  screenManager->PushScreen("DRAW", &draw);
  screenManager->ShowScreen("DRAW");

  while (screenManager->IsRunning())
  {
    screenManager->Update();
    screenManager->Draw();
  }

  ScreenManager::DestroyInstance();
  
  return 0;
}