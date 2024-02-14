#pragma once
#include <iostream>
#include <SDL2/SDL.h>
#include "Window.h"

class Application {
public:
  Application(Window* window) : mWindow { window } {
    mRenderer = SDL_CreateRenderer(mWindow->GetSDLWindow(), -1, SDL_RENDERER_ACCELERATED);
    if (mRenderer == nullptr) {
      // Handle renderer creation failure
      std::cerr << "Failed to create renderer! SDL Error: " << SDL_GetError() << std::endl;
    }
  }

  ~Application() {
    SDL_DestroyRenderer(mRenderer);
  }

  SDL_Surface* GetWindowSurface() const {
    return mWindow->GetSurface();
  }

  SDL_Renderer* GetRenderer() const {
    return mRenderer;
  }

  SDL_Window *GetWindow() const {
    return mWindow->GetSDLWindow();
  }

  void Quit();

private:
  Window* mWindow;
  SDL_Renderer* mRenderer;
};
