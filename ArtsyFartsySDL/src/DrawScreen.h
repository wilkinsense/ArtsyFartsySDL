#pragma once

#include "Screens\Screen.h"
#include <map>
#include <vector>

class Instrument;
struct SDL_Texture;

class ColourButton;
class InstrumentButton;

class DrawScreen : public Screen
{
public:
  DrawScreen();
  ~DrawScreen();

  void OnEnter();
  void OnExit();
  
  void Update(const SDL_Event &e);
  void Draw(SDL_Renderer *renderer);

protected:
  std::map<int, Instrument *> mInstruments;

  SDL_Texture *mButtonTexture;
  SDL_Texture *mPencilTexture;
  SDL_Texture *mSprayTexture;
  SDL_Texture *mConfettiTexture;

  std::vector<ColourButton *> mButtons;
  InstrumentButton *mPencilButton;
  InstrumentButton *mSprayButton;
  std::map<int, InstrumentButton *> mInstrumentButtons;

  void CheckInput(SDL_Event e);
  bool IsWithinButton(int x, int y, ColourButton **button);

  int mButtonsX, mButtonsY;
  int mButtonsOffsetX, mButtonsOffsetY;
  bool mWithinButtons;

  SDL_Texture *mBackBuffer;
};