#pragma once
#include "command.h"
#include "image.h"
#include "imgui/imgui_internal.h"
#include "levels.h"

struct GameData {
  const float* dt;
  ImGuiContext* imGui_context;
  Image* fallback;
  Image* wall;
  Image* ground;
  Image* player;
  Image* box;
  Memory::Arena* arena_levels;
  Memory::Arena* arena_images;
  Memory::Arena* arena_entities;
  Memory::Arena* arena_commands;
  CommandBuffer* commandBuffer;
  LevelData* levels;
  int currentLevelIndex;
  int levelCount;
  int currentLevel;
  bool* keys_previous;
  LevelData* GetCurrentLevel(){
    return &levels[currentLevelIndex];
  }
    
};



