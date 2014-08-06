#pragma once
#include <SDL_events.h>
#include <vector>

class Screen
{
  virtual void Update(const SDL_EventType &type) = 0;
  virtual void Draw() = 0;
};

class ScreenManager
{
public:
  static ScreenManager* GetInstance();
  void ShowScreen(Screen *screen);

protected:
  static ScreenManager *kInstance;

  std::vector<Screen *> mScreens;
};