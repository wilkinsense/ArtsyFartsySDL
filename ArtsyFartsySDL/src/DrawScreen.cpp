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
  const float adjustment = 1.0001f;
  static float modifier = 1.0f;
  if (modifier > 1.0f)
  {
    modifier *= 0.99f;
    if (modifier < 1.0f)
    {
      modifier = 1.0f;
    }
  }
  //printf("Modifier: %f\n", modifier);

  const std::vector<Shape *>* shapes = InstrumentManager::GetInstance()->GetActiveShapes();
  for (auto shapeItr = shapes->begin(); shapeItr != shapes->end(); shapeItr++)
  {
    Shape *currentShape = (*shapeItr);
    if (currentShape->drawn == false)
    {
      const std::vector<ShapeBlock *>* shapeBlocks = currentShape->GetBlocks();

      for (unsigned int blockIndex = 0; blockIndex < shapeBlocks->size(); blockIndex++)
      {
        ShapeBlock *block = shapeBlocks->at(blockIndex);

        int x1 = block->x;
        int y1 = block->y;
        int x2 = block->x;
        int y2 = block->y;
        int brushSize = currentShape->brushType == BRUSHTYPE_PENCIL ? block->brushSize / 2 : block->brushSize;
        bool willDraw = (block->drawn == false);

        if (blockIndex + 1 < shapeBlocks->size())
        {
          ShapeBlock *block2 = shapeBlocks->at(blockIndex + 1);
          x2 = block2->x;
          y2 = block2->y;

          int difference = (block2->timestamp - block->timestamp);
          if (difference < 0)
          {
            difference = 0;
          }

          brushSize = block->brushSize;

          if ((blockIndex == 0 && shapeBlocks->size() == 2) && currentShape->brushType == BRUSHTYPE_PENCIL)
          {
            willDraw = true;
          }
          //brushSize = block2->brushSize + (difference / 10.0f);
        }
        else if (shapeBlocks->size() > 1)
        {
          continue;
        }

        if (willDraw)
        {
          int variance = block->brushSize * 10;

          switch (currentShape->brushType)
          {
          case BRUSHTYPE_PENCIL:
            thickLineRGBA(renderer,
              x1, y1, x2, y2,
              brushSize,
              block->brushColor.r, block->brushColor.g, block->brushColor.b, block->brushColor.a);
            break;

          case BRUSHTYPE_CONFETTI:
            thickLineRGBA(renderer,
              x1 + (rand() % variance) - (block->brushSize * 5), 
              y1 + (rand() % variance) - (block->brushSize * 5), 
              x2 + (rand() % variance) - (block->brushSize * 5),
              y2 + (rand() % variance) - (block->brushSize * 5),
              brushSize,
              block->brushColor.r - (rand() % 50), 
              block->brushColor.g - (rand() % 50), 
              block->brushColor.b - (rand() % 50), 
              block->brushColor.a);
            break;

          default:

            break;
          }

          /*thickLineRGBA(renderer,
            x1 + 5, y1 + 5, x2 + 5, y2 + 5,
            block->brushSize,
            block->brushColor.r, block->brushColor.g, block->brushColor.b, block->brushColor.a);*/

          block->drawn = true;
        }
      }
    }
  }
}