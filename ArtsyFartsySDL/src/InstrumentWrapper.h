#pragma once
#include "InstrumentManager.h"
#include "InputManager.h"

class InstrumentWrapper
{
public:
  static void InputBegan(SDL_Event e)
  {
    InstrumentManager *im = InstrumentManager::GetInstance();
    im->InputBegan(e);
    InputManager::GetInstance()->AssignEvent(SDL_MOUSEBUTTONUP, (InputEvent)&InstrumentWrapper::InputEnded);
    InputManager::GetInstance()->AssignEvent(SDL_MOUSEMOTION, (InputEvent)&InstrumentWrapper::InputMoved);
  }

  static void InputMoved(SDL_Event e)
  {
    static int lastX = 0, lastY = 0;

    SDL_MouseMotionEvent mme = e.motion;

    if (lastX != mme.x || lastY != mme.y)
    {
      InstrumentManager *im = InstrumentManager::GetInstance();
      im->InputMoved(e); 
      lastX = mme.x;
      lastY = mme.y;
    }
  }

  static void InputEnded(SDL_Event e)
  {
    InstrumentManager *im = InstrumentManager::GetInstance();
    im->InputEnded(e);
    InputManager::GetInstance()->RemoveEvent(SDL_MOUSEBUTTONUP, (InputEvent)&InstrumentWrapper::InputEnded);
    InputManager::GetInstance()->RemoveEvent(SDL_MOUSEMOTION, (InputEvent)&InstrumentWrapper::InputMoved);
  }
};