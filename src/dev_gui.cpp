#include "dev_gui.h"
#include "SDL3/SDL_scancode.h"
#include "gameState.h"
#include "command.h"
#include "imgui/imgui_impl_sdl3.h"
#include "imgui/imgui_impl_sdlrenderer3.h"
#include "SDL3/SDL_render.h"
#include <string>

using namespace std;

void DEV::Initialize(SDL_Window* window, SDL_Renderer* renderer){
  ImGui::CreateContext();
  ImGui_ImplSDL3_InitForSDLRenderer(window, renderer);
  ImGui_ImplSDLRenderer3_Init(renderer);

  ImGuiIO& io = ImGui::GetIO();

  int w, h;
  SDL_GetWindowSize(window, &w, &h);
  io.DisplaySize = ImVec2((float)w, (float)h);  
}

void DEV::ProcessEvents(SDL_Event* event){
  ImGui_ImplSDL3_ProcessEvent(event);
}

void DEV::PreDraw(){
  ImGui::NewFrame();
}
