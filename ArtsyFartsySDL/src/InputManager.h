#pragma once
#include <map>
#include <SDL_events.h>
#include <vector>

class IInput { };
typedef void(*InputEvent)(SDL_Event e);
typedef void(IInput::* InputMemberEvent)(SDL_Event e);

class InputBlock;
struct InputPair;

class InputManager
{
public:
    static InputManager* GetInstance();
    static void DestroyInstance();

    InputManager();
    ~InputManager();

    void AssignEvent(SDL_EventType evt, InputEvent callback);
    void AssignEvent(SDL_EventType evt, void* target, InputMemberEvent callback);

    void RemoveEvent(SDL_EventType evt, InputEvent callback);
    void RemoveEvent(SDL_EventType evt, void* target, InputMemberEvent callback);

    void ProcessEvent(SDL_Event e);

protected:
    static InputManager* kInstance;
    std::map<SDL_EventType, std::vector<InputBlock*> > mEventMap;
    std::map<SDL_EventType, std::vector<InputPair*> > mMemberEventMap;
};