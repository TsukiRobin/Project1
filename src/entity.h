#pragma once
#include <cstdint>
#include <cassert>

enum Behaviour : uint32_t {
  NONE = 0, // 1
  CAN_MOVE = 1 << 0, // 2
  IS_PLAYER = 1 << 1, // 4
  RESPOND_TO_INPUT = 1 << 2 // 8
};


enum class ID : uint8_t {
  NONE = 0,
  GROUND = 1,
  PLAYER = 2,
  WALL = 3,
  BOX = 4
};



struct Entity {
  ID  id;
  int x;
  int y;
  Behaviour behaviour;

  bool HasBehaviour(Behaviour flags){
    return (behaviour & flags) == flags;
  }

  void SetBehaviour(Behaviour flags){
    behaviour = flags;
  }

  void AddBehaviour(Behaviour flags){
    behaviour = (Behaviour)(behaviour | flags);
  }

  void RemoveBehaviour(Behaviour flags){
    behaviour = (Behaviour)(behaviour & ~flags);
  }

  void InitializeBaseBehaviour(){
    assert(id != ID::NONE);
    switch(id) {
      default:
        SetBehaviour(NONE);
        break;
      case ID::PLAYER:
        SetBehaviour((Behaviour)(CAN_MOVE | IS_PLAYER | RESPOND_TO_INPUT));
          break;

      case ID::BOX:
        SetBehaviour((Behaviour)CAN_MOVE);
        break;
    }
  }
};

