#include "DrawScreen.h"
#include "InputManager.h"
#include "InstrumentWrapper.h"
#include "Shape.h"
#include <SDL2_gfxPrimitives.h>

DrawScreen::DrawScreen() { }

DrawScreen::~DrawScreen() { }

void DrawScreen::OnEnter()
{
  InputManager::GetInstance()->AssignEvent(SDL_MOUSEBUTTONDOWN, (InputEvent)(&InstrumentWrapper::InputBegan));
}

void DrawScreen::OnExit()
{
  InputManager::GetInstance()->RemoveEvent(SDL_MOUSEBUTTONDOWN, (InputEvent)(&InstrumentWrapper::InputBegan));
  InputManager::GetInstance()->RemoveEvent(SDL_MOUSEMOTION, (InputEvent)(&InstrumentWrapper::InputMoved));
  InputManager::GetInstance()->RemoveEvent(SDL_MOUSEBUTTONUP, (InputEvent)(&InstrumentWrapper::InputEnded));
}

void DrawScreen::Update(const SDL_EventType &type)
{
  InputManager::GetInstance()->ProcessEvent(type);
}

void DrawScreen::Draw(SDL_Renderer *renderer)
{
  const std::vector<Shape *>* shapes = InstrumentManager::GetInstance()->GetActiveShapes();
  for (auto shapeItr = shapes->begin(); shapeItr != shapes->end(); shapeItr++)
  {
    Shape *currentShape = (*shapeItr);
    if (currentShape->drawn == false)
    {
      const std::vector<ShapeBlock *>* shapeBlocks = currentShape->GetBlocks();

      for (unsigned int blockIndex = 0; blockIndex < shapeBlocks->size(); blockIndex++)
      {
        if (blockIndex + 1 < shapeBlocks->size())
        {
          ShapeBlock *block1 = shapeBlocks->at(blockIndex);
          ShapeBlock *block2 = shapeBlocks->at(blockIndex + 1);

          if (block1->drawn == false)
          {
            int x1 = block1->x;
            int y1 = block1->y;
            int x2 = block2->x;
            int y2 = block2->y;

            thickLineRGBA(renderer,
              x1, y1, x2, y2,
              block1->brushSize,
              block1->brushColor.r, block1->brushColor.g, block1->brushColor.b, block1->brushColor.a);

            block1->drawn = true;
          }
        }
      }
    }
  }
}