#include "ScreenManager.h"
#include "Screens\Screen.h"
#include <SDL.h>

ScreenManager* ScreenManager::kInstance = nullptr;

ScreenManager* ScreenManager::GetInstance()
{
  if (kInstance == nullptr)
  {
    kInstance = new ScreenManager();
  }

  return kInstance;
}

void ScreenManager::DestroyInstance()
{
  if (kInstance != nullptr)
  {
    delete kInstance;
    kInstance = nullptr;
  }
}

ScreenManager::ScreenManager()
{
  SDL_Init(SDL_INIT_AUDIO | SDL_INIT_VIDEO);

  mWindow = SDL_CreateWindow("Artsy Fartsy", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1000, 500, SDL_WINDOW_SHOWN);
  mRenderer = SDL_CreateRenderer(mWindow, -1, SDL_RENDERER_ACCELERATED);

  mActiveScreen = nullptr;
  mIsRunning = true;
}

ScreenManager::~ScreenManager()
{
  SDL_DestroyRenderer(mRenderer);
  SDL_DestroyWindow(mWindow);

  SDL_Quit();
}

bool ScreenManager::ShowScreen(std::string id)
{
  bool success = false;
  auto screenItr = mScreens.find(id);
  if (screenItr != mScreens.end())
  {
    if (mActiveScreen != nullptr)
    {
      mActiveScreen->OnExit();
    }

    ClearRenderer();

    mActiveScreen = screenItr->second;
    mActiveScreen->OnEnter();
    success = true;
  }

  return success;
}

bool ScreenManager::PushScreen(std::string id, Screen *screen)
{
  bool success = false;
  if (screen != nullptr)
  {
    auto screenItr = mScreens.find(id);
    if (screenItr == mScreens.end())
    {
      std::pair<std::string, Screen *> entry(id, screen);
      mScreens.insert(entry);
    }
  }

  return success;
}

bool ScreenManager::PopScreen(std::string id)
{
  bool success = false;
  auto screenItr = mScreens.find(id);
  if (screenItr != mScreens.end())
  {
    if (screenItr->second == mActiveScreen)
    {
      mActiveScreen->OnExit();
      mActiveScreen = nullptr;
    }

    mScreens.erase(screenItr);
  }

  return success;
}

void ScreenManager::Update()
{
  if (mIsRunning)
  {
    SDL_Event e;
    SDL_PollEvent(&e);

    if (mActiveScreen)
    {
      mActiveScreen->Update(e);
    }

    if (e.type == SDL_QUIT)
    {
      mIsRunning = false;
    }
  }
}

void ScreenManager::Draw()
{
  if (mActiveScreen)
  {
    mActiveScreen->Draw(mRenderer);
  }

  SDL_RenderPresent(mRenderer);
  SDL_UpdateWindowSurface(mWindow);
}

bool ScreenManager::IsRunning()
{
  return mIsRunning;
}

void ScreenManager::SetIsRunning(bool running)
{
  mIsRunning = running;
}

void ScreenManager::ClearRenderer()
{
  SDL_SetRenderDrawColor(mRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
  SDL_RenderClear(mRenderer);
}

SDL_Renderer* ScreenManager::GetRenderer() const
{
  return mRenderer;
}
