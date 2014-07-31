#pragma once
#include "InstrumentManager.h"
#include "InputManager.h"

class InstrumentWrapper
{
public:
  static void InputBegan()
  {
    InstrumentManager *im = InstrumentManager::GetInstance();
    im->InputBegan();
    InputManager::GetInstance()->RemoveEvent(SDL_MOUSEBUTTONDOWN, (InputEvent)&InstrumentWrapper::InputBegan);
    InputManager::GetInstance()->AssignEvent(SDL_MOUSEBUTTONUP, (InputEvent)&InstrumentWrapper::InputEnded);
    InputManager::GetInstance()->AssignEvent(SDL_MOUSEMOTION, (InputEvent)&InstrumentWrapper::InputMoved);
  }

  static void InputMoved()
  {
    InstrumentManager *im = InstrumentManager::GetInstance();
    im->InputMoved();
  }

  static void InputEnded()
  {
    InstrumentManager *im = InstrumentManager::GetInstance();
    im->InputEnded();
    InputManager::GetInstance()->RemoveEvent(SDL_MOUSEBUTTONUP, (InputEvent)&InstrumentWrapper::InputEnded);
    InputManager::GetInstance()->RemoveEvent(SDL_MOUSEMOTION, (InputEvent)&InstrumentWrapper::InputMoved);
    InputManager::GetInstance()->AssignEvent(SDL_MOUSEBUTTONDOWN, (InputEvent)&InstrumentWrapper::InputBegan);
  }
};