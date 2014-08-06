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
  SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

  TestClass c;
  InputManager::GetInstance()->AssignEvent(SDL_KEYDOWN, &c, (InputMemberEvent)(&TestClass::CallAThing));

  InputManager::GetInstance()->AssignEvent(SDL_MOUSEBUTTONDOWN, (InputEvent)(&InstrumentWrapper::InputBegan));

  //SDL_ShowWindow(window);
  bool quit = false;
  while (!quit)
  {
    //surface = SDL_GetWindowSurface(window);
    SDL_SetRenderDrawColor(renderer, 0xFA, 0xF0, 0x00, 0xFF);
    SDL_RenderClear(renderer);

    //SDL_FillRect(surface, NULL, SDL_MapRGB(surface->format, 0xFA, 0xF0, 0x00));
    //SDL_RenderSetScale(renderer, 5.0f, 5.0f);

    const std::vector<HistoryBlock *>* activeBlocks = HistoryManager::GetInstance()->GetActiveBlocks();
    for (int i = 0; i < activeBlocks->size(); i++)
    {
      if (i + 1 < activeBlocks->size())
      {
        int x1 = activeBlocks->at(i)->x;
        int y1 = activeBlocks->at(i)->y;
        
        int x2 = activeBlocks->at(i + 1)->x;
        int y2 = activeBlocks->at(i + 1)->y;

        thickLineRGBA(renderer, x1, y1, x2, y2, 2, 0, 255, 0, 255);

        
      }
    }

    //SDL_RenderSetScale(renderer, 1.0f, 1.0f);

    SDL_RenderPresent(renderer);
 
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

  SDL_DestroyRenderer(renderer);
  SDL_DestroyWindow(window);

  SDL_Quit();
  return 0;
}