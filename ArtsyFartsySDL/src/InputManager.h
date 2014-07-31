#pragma once
#include <SDL_events.h>
#include <map>
#include <vector>

class IInput { };
typedef void(*InputEvent)();
typedef void(IInput::*InputMemberEvent)();

class InputBlock;
class InputPair;

class InputManager
{
public:
  static InputManager* GetInstance();
  static void DestroyInstance();

  ~InputManager();

  void AssignEvent(SDL_EventType evt, InputEvent callback);
  void AssignEvent(SDL_EventType evt, void *target, InputMemberEvent callback);

  void RemoveEvent(SDL_EventType evt, InputEvent callback);
  void RemoveEvent(SDL_EventType evt, void *target, InputMemberEvent callback);

  void ProcessEvent(SDL_EventType evt);

protected:
  InputManager();

  static InputManager *kInstance;
  std::map<SDL_EventType, std::vector<InputBlock *> > mEventMap;
  std::map<SDL_EventType, std::vector<InputPair *> > mMemberEventMap;
};