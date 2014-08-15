#include "InputManager.h"

class InputBlock
{
public:
  InputBlock(InputEvent callback) : callback(callback) { }
  void ProcessInput(SDL_Event e)
  {
    (*callback)(e);
  }

  InputEvent callback;

};

struct InputPair
{
  void *target;
  InputMemberEvent callback;

  InputPair(void *target, InputMemberEvent callback) : target(target), callback(callback) { }
  void ProcessInput(SDL_Event e)
  {
    IInput *castedTarget = (IInput *)target;
    (castedTarget->*callback)(e);
  }
};

InputManager* InputManager::kInstance = NULL;

InputManager* InputManager::GetInstance()
{
  if (kInstance == NULL)
  {
    kInstance = new InputManager();
  }

  return kInstance;
}

void InputManager::DestroyInstance()
{
  if (kInstance != NULL)
  {
    delete kInstance;
    kInstance = NULL;
  }
}

InputManager::InputManager() { }
InputManager::~InputManager() { }

void InputManager::AssignEvent(SDL_EventType evt, InputEvent callback)
{
  InputBlock *newBlock = new InputBlock(callback);

  auto mapItr = mEventMap.find(evt);
  if (mapItr == mEventMap.end())
  {
    std::pair<SDL_EventType, std::vector<InputBlock *> > newPair(evt, std::vector<InputBlock *> { newBlock });
    mEventMap.insert(newPair);
  }
  else
  {
    bool found = false;
    std::vector<InputBlock *> &events = mapItr->second;
    for (auto itr = events.begin(); itr != events.end(); itr++)
    {
      InputBlock *currentBlock = (*itr);
      if (currentBlock->callback == callback)
      {
        /* If the block already exists in our list, we want to remove it.*/
        found = true;
        delete newBlock;
        break;
      }
    }

    if (found == false)
    {
      events.push_back(newBlock);
    }
  }
}

void InputManager::AssignEvent(SDL_EventType evt, void *target, InputMemberEvent callback)
{
  IInput *castedTarget = (IInput *)target;

  InputPair *newPair = new InputPair(castedTarget, callback);

  auto mapItr = mMemberEventMap.find(evt);
  if (mapItr == mMemberEventMap.end())
  {
    std::pair<SDL_EventType, std::vector<InputPair *> > newEntry(evt, std::vector<InputPair *> { newPair });
    mMemberEventMap.insert(newEntry);
  }
  else
  {
    bool found = false;
    std::vector<InputPair *> &events = mapItr->second;
    for (auto itr = events.begin(); itr != events.end(); itr++)
    {
      InputPair *currentPair = (*itr);
      if (currentPair->target == target && currentPair->callback == callback)
      {
        found = true;
        delete newPair;
        break;
      }
    }

    if (found == false)
    {
      events.push_back(newPair);
    }
  }
}

void InputManager::RemoveEvent(SDL_EventType evt, InputEvent callback)
{
  auto mapItr = mEventMap.find(evt);
  if (mapItr != mEventMap.end())
  {
    bool found = false;
    std::vector<InputBlock *> &events = mapItr->second;

    auto itr = events.begin();
    for (; itr != events.end(); itr++)
    {
      InputBlock *currentBlock = (*itr);
      if (currentBlock->callback == callback)
      {
        found = true;
        break;
      }
    }

    if (found == true)
    {
      delete (*itr);
      events.erase(itr);

      // If there aren't any more events for this key, remove it.
      if (events.empty() == true)
      {
        mEventMap.erase(evt);
      }
    }
  }
}

void InputManager::RemoveEvent(SDL_EventType evt, void *target, InputMemberEvent callback)
{
  auto mapItr = mMemberEventMap.find(evt);
  if (mapItr != mMemberEventMap.end())
  {
    bool found = false;
    std::vector<InputPair *> &events = mapItr->second;

    auto itr = events.begin();
    for (; itr != events.end(); itr++)
    {
      InputPair *currentPair = (*itr);
      if (currentPair->target == target && currentPair->callback == callback)
      {
        found = true;
        break;
      }
    }

    if (found == true)
    {
      delete (*itr);
      events.erase(itr);

      // If there aren't any more events for this key, remove it.
      if (events.empty() == true)
      {
        mEventMap.erase(evt);
      }
    }
  }
}

void InputManager::ProcessEvent(SDL_Event e)
{
  SDL_EventType evt = (SDL_EventType)e.type;
  auto mapItr = mEventMap.find(evt);
  if (mapItr != mEventMap.end())
  {
    std::vector<InputBlock *> events = mapItr->second;
    for (auto itr = events.begin(); itr != events.end(); itr++)
    {
      (*itr)->ProcessInput(e);
    }
  }

  auto memberMapItr = mMemberEventMap.find(evt);
  if (memberMapItr != mMemberEventMap.end())
  {
    std::vector<InputPair *> events = memberMapItr->second;
    for (auto itr = events.begin(); itr != events.end(); itr++)
    {
      (*itr)->ProcessInput(e);
    }
  }
}

