//#include <AK/SoundEngine/Common/AkSoundEngine.h>
#include "HistoryManager.h"
#include "InputManager.h"
#include "Instruments/InstrumentWrapper.h"
#include "Screens/DrawScreen.h"
#include "Screens/ReplayScreen.h"
#include "Screens/ScreenManager.h"
#include <Windows.h>
#include <gl/GL.h>
#include <gl/GLU.h>
#include <iostream>
#include <SDL.h>
#include <SDL2_gfxPrimitives.h>
#include <stdio.h>

#define MAX_BRUSH_SIZE 20
#define MIN_BRUSH_SIZE 2

class TestClass
{
public:
    void InputDispatch(SDL_Event e);
    void ClearScreen();
    void ShowReplay();

    void IncreaseBrushSize();
    void DecreaseBrushize();
};

bool showingReplay = false;

int main(int argc, char** argv)
{
    TestClass c;
    InputManager::GetInstance()->AssignEvent(SDL_KEYDOWN, &c, (InputMemberEvent)(&TestClass::InputDispatch));

    DrawScreen draw;
    ReplayScreen replay;

    HistoryManager::GetInstance()->SetRandomSeed(time(0));

    ScreenManager* screenManager = ScreenManager::GetInstance();
    screenManager->PushScreen("DRAW", &draw);
    screenManager->PushScreen("REPLAY", &replay);

    screenManager->ShowScreen("DRAW");

    while (screenManager->IsRunning())
    {
        screenManager->Update();
        screenManager->Draw();
    }

    ScreenManager::DestroyInstance();

    return 0;
}


void TestClass::InputDispatch(SDL_Event e)
{
    SDL_KeyboardEvent ke = e.key;
    SDL_Keycode kc = ke.keysym.sym;
    switch (kc)
    {
    case SDLK_SPACE:
        ShowReplay();
        break;

    case SDLK_ESCAPE:
        ClearScreen();
        break;

    case SDLK_z:
        DecreaseBrushize();
        break;

    case SDLK_x:
        IncreaseBrushSize();
        break;
    }
}

void TestClass::ClearScreen()
{
    if (showingReplay == false)
    {
        InstrumentManager::GetInstance()->ClearAllShapes();
        ScreenManager::GetInstance()->ClearRenderer();
    }
}

void TestClass::ShowReplay()
{
    ScreenManager* sm = ScreenManager::GetInstance();
    if (showingReplay == false)
    {
        sm->ShowScreen("REPLAY");
        showingReplay = true;
    }
    else
    {
        sm->ShowScreen("DRAW");
        showingReplay = false;
    }

}

void TestClass::IncreaseBrushSize()
{
    InstrumentManager* im = InstrumentManager::GetInstance();
    int brushSize = im->GetBrushSize() + 1;
    if (brushSize > MAX_BRUSH_SIZE)
    {
        brushSize = MAX_BRUSH_SIZE;
    }

    im->SetBrushSize(brushSize);
}

void TestClass::DecreaseBrushize()
{
    InstrumentManager* im = InstrumentManager::GetInstance();
    int brushSize = im->GetBrushSize() - 1;
    if (brushSize < MIN_BRUSH_SIZE)
    {
        brushSize = MIN_BRUSH_SIZE;
    }

    im->SetBrushSize(brushSize);
}