#include <SDL.h>
#include <stdio.h>
#include <iostream>
#include <AK\SoundEngine\Common\AkSoundEngine.h>
#include "InputManager.h"
#include "InstrumentWrapper.h"

class TestClass
{
public:
  void CallAThing()
  {
    printf("Thing is called.\n");
    InputManager::GetInstance()->RemoveEvent(SDL_KEYDOWN, this, (InputMemberEvent)&TestClass::CallAThing);
    InputManager::GetInstance()->AssignEvent(SDL_KEYDOWN, this, (InputMemberEvent)&TestClass::CallAnotherThing);
  }

  void CallAnotherThing()
  {
    printf("This other thing is called.\n");
    InputManager::GetInstance()->RemoveEvent(SDL_KEYDOWN, this, (InputMemberEvent)&TestClass::CallAnotherThing);
    InputManager::GetInstance()->AssignEvent(SDL_KEYDOWN, this, (InputMemberEvent)&TestClass::CallAThing);
  }
};

int main(int argc, char ** argv)
{
  SDL_Init(SDL_INIT_AUDIO | SDL_INIT_VIDEO);

  SDL_Window *window = SDL_CreateWindow("Artsy Fartsy", 100, 100, 500, 500, SDL_WINDOW_SHOWN);
  SDL_Surface *surface = NULL;

  SDL_Event e;

  TestClass c;
  InputManager::GetInstance()->AssignEvent(SDL_KEYDOWN, &c, (InputMemberEvent)(&TestClass::CallAThing));

    InputManager::GetInstance()->AssignEvent(SDL_MOUSEBUTTONDOWN, (InputEvent)(&InstrumentWrapper::InputBegan));

  //SDL_ShowWindow(window);
  bool quit = false;
  while (!quit)
  {
    surface = SDL_GetWindowSurface(window);

    SDL_FillRect(surface, NULL, SDL_MapRGB(surface->format, 0xFA, 0xF0, 0x00));

    SDL_UpdateWindowSurface(window);

    SDL_PollEvent(&e);
    if (e.type == SDL_KEYDOWN)
    {
      printf("Debug information.\n");
      //quit = true;
    }
    else if (e.type == SDL_QUIT)
    {
      quit = true;
    }
    else if (e.type == SDL_MOUSEBUTTONDOWN)
    {
      //printf("Mouse is down at.\n");
    }
    else if (e.type == SDL_MOUSEBUTTONUP)
    {
      //printf("Mouse is up at.\n");
    }
    else if (e.type == SDL_MOUSEMOTION)
    {
      //printf("Mouse is moving at.\n");
    }

    InputManager::GetInstance()->ProcessEvent((SDL_EventType)e.type);
  }

  SDL_DestroyWindow(window);

  SDL_Quit();
  return 0;
}