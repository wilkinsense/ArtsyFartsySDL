#pragma once
#include <SDL_events.h>
#include <map>
#include <string>

struct SDL_Renderer;

class Screen
{
public:
  virtual void Update(const SDL_EventType &type) = 0;
  virtual void Draw(SDL_Renderer *renderer) = 0;

  virtual void OnEnter() { }
  virtual void OnExit() { }
};

class ScreenManager
{
public:
  static ScreenManager* GetInstance();
  static void DestroyInstance();

  ~ScreenManager();

  bool ShowScreen(std::string id);
  bool PushScreen(std::string id, Screen *screen);
  bool PopScreen(std::string id);

  void Update();
  void Draw();

  bool IsRunning();
  void SetIsRunning(bool running);

protected:
  static ScreenManager *kInstance;
  ScreenManager();

  std::map<std::string, Screen *> mScreens;
  Screen *mActiveScreen;

  SDL_Window *mWindow;
  SDL_Renderer *mRenderer;

  bool mIsRunning;
};