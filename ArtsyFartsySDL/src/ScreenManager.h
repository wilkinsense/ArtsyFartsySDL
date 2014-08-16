#pragma once
#include <SDL_events.h>
#include <map>
#include <string>

struct SDL_Renderer;
class Screen;

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

  SDL_Renderer* GetRenderer() const;
  SDL_Window* GetWindow() const;

protected:
  static ScreenManager *kInstance;
  ScreenManager();

  void ClearRenderer();

  std::map<std::string, Screen *> mScreens;
  Screen *mActiveScreen;

  SDL_Window *mWindow;
  SDL_Renderer *mRenderer;

  bool mIsRunning;
};