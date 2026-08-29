#pragma once
#include "SDL3/SDL_rect.h"
#include "image.h"
#include "levels.h"


struct GameData {
  Image* fallback;
  Image* wall;
  Image* ground;
  Image* player;
  Image* box;
  Memory::Arena* arena_levels;
  Memory::Arena* arena_images;
  Memory::Arena* arena_entities;
  LevelData* levels;
  int currentLevelIndex;
  LevelData* GetCurrentLevel(){
    return &levels[currentLevelIndex];
  }
  int levelCount;
  int currentLevel;
  bool* keys_previous;
    
};



