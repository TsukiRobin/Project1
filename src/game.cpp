#include <cstdio>
#include <cstring>
#include <windows.h>
#include <winnt.h>
#include "game.h"
#include "SDL3/SDL_scancode.h"
#include "levelRenderer.h"
#include "levels.h"



extern "C"{
void Initialize(GameData* data, SDL_Renderer* renderer) {
  data->ground = AssetManagement::LoadSprite(data->arena_images, renderer, "ground.png");
  printf("Initialized Ground\n");
  data->wall = AssetManagement::LoadSprite(data->arena_images, renderer, "wall.png");
  printf("Initialized Wall\n");
  data->player = AssetManagement::LoadSprite(data->arena_images, renderer, "player.png");
  printf("Initialized Player\n");
  data->fallback = AssetManagement::LoadSprite(data->arena_images, renderer, "fallback.png");
  printf("Initialized Fallback\n");
  data->box = AssetManagement::LoadSprite(data->arena_images, renderer, "box.png");
  printf("Initialized Box\n");
  data->currentLevel = 0;
  printf("Creating Level\n");
  CreateLevel(data->arena_levels, &data->levels[0], "assets/levels/testLevel.tmj");
  CreateLevel(data->arena_levels, &data->levels[1], "assets/levels/testLevel_box.tmj");
  printf("Level Created, Creating entities\n");
  CreateEntities(data->arena_entities, &data->levels[data->currentLevel]);
  printf("Entities Created!\n");
  }
}

bool TryMove(Entity *mover, LevelData *level, CommandBuffer* cmd_buffer, int xDir, int yDir) {
  if(mover->HasBehaviour(CAN_MOVE) == false){
    return false;
   }
   int test_x = mover->x + xDir;
   int test_y = mover->y + yDir;
   Entity* stepInto_entity = level->GetEntity(test_x, test_y);
   ID stepInto_tile_id = (ID)level->GetCellID(test_x, test_y);


   
   if(stepInto_entity == nullptr){
     if (stepInto_tile_id == ID::GROUND){
        MoveCommand mv;
        mv.type = CMD_TYPE::MOVE;
        mv.entity = mover;
        mv.xDir = xDir;
        mv.yDir = yDir;
        Push(cmd_buffer, mv);
        return true;
     }
     return false;
   }

   if(stepInto_entity->HasBehaviour(CAN_MOVE)){
     if(TryMove(stepInto_entity, level, cmd_buffer,xDir, yDir)){
      MoveCommand mv;
      mv.type = CMD_TYPE::MOVE;
      mv.entity = mover;
      mv.xDir = xDir;
      mv.yDir = yDir;
      Push(cmd_buffer, mv);
      return true;
       
     }
   }
   return false;
}

bool KeyPressed(SDL_Scancode key, const bool* current, const bool* previous){
  if (previous == nullptr){
    return current[key];
  }
  return current[key] && !previous[key];
}

bool KeyHeld(SDL_Scancode key, const bool* current, const bool* previous){
  if (previous == nullptr){
    return false;      
  }
  return current[key] && previous[key];
}

bool KeyReleased(SDL_Scancode key, const bool* current, const bool* previous){
  if(previous == nullptr){
    return false;
  }
  return !current[key] && previous[key];
}


bool HandleEvents(GameData *data, SDL_Event event){

  if(event.type != SDL_EVENT_KEY_DOWN){
    return true;
  }

  if (event.key.key == SDLK_ESCAPE){
   return false;
 }

 return true;
}

void Update(GameData* data, float dt){

  const bool* keys = SDL_GetKeyboardState(nullptr);

  for (int i = 0; i < data->GetCurrentLevel()->entityCount; i++){
    Entity* entity = &data->GetCurrentLevel()->entityBuffer[i];

    if(entity->HasBehaviour((Behaviour)(Behaviour::RESPOND_TO_INPUT | Behaviour::CAN_MOVE))){
      int xChange = 0;
      int yChange = 0;
      
      if (KeyPressed(SDL_SCANCODE_RIGHT, keys, data->keys_previous)){
        xChange = 1;
      }
      else if(KeyPressed(SDL_SCANCODE_LEFT, keys, data->keys_previous)){
        xChange = -1;
      }
      else if(KeyPressed(SDL_SCANCODE_UP, keys, data->keys_previous)){
        yChange = -1;
      }
      else if(KeyPressed(SDL_SCANCODE_DOWN, keys, data->keys_previous)){
        yChange = 1;
      }    

      if(KeyPressed(SDL_SCANCODE_Z, keys, data->keys_previous)){
        if(KeyHeld(SDL_SCANCODE_LSHIFT, keys, data->keys_previous)){
          Redo(data->commandBuffer);
      }
        else{
          Undo(data->commandBuffer);
      }
  }


    if (xChange != 0 || yChange != 0){
      TryMove(entity, data->GetCurrentLevel(), data->commandBuffer, xChange, yChange);
      }
    }


  }
  memcpy((void*)data->keys_previous, keys, SDL_SCANCODE_COUNT * sizeof(bool));
}


void Draw(GameData* data, SDL_Renderer* renderer){
  SDL_SetRenderDrawColor(renderer, 120, 70, 120, 255);
  SDL_RenderClear(renderer);


  RenderLevel(data, renderer);
  RenderEntities(data, renderer);
  SDL_RenderPresent(renderer);
}

void OnQuit(SDL_Renderer* renderer){
  SDL_DestroyRenderer(renderer);

}

