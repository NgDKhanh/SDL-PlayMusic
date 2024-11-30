#pragma once
#include <iostream>
#include <SDL2/SDL.h>
#include <vector>
#include <memory>
#include "Window.h"
#include "Texture.h"

class Application {
public:
  Application(Window* window) : mWindow { window } {
    mRenderer = std::shared_ptr<SDL_Renderer>(SDL_CreateRenderer(mWindow->GetSDLWindow(), -1, SDL_RENDERER_ACCELERATED), SDL_DestroyRenderer);
    if (mRenderer == nullptr) {
      // Handle renderer creation failure
      std::cerr << "Failed to create renderer! SDL Error: " << SDL_GetError() << std::endl;
    }
  }

  ~Application() {
    // SDL_DestroyRenderer(mRenderer.get());
  }

  SDL_Surface* GetWindowSurface() const {
    return mWindow->GetSurface();
  }

  SDL_Renderer* GetRenderer() const {
    return mRenderer.get();
  }

  SDL_Window *GetWindow() const {
    return mWindow->GetSDLWindow();
  }

  void Quit();

  void SubscribeToRender(LTexture* RenderedObject) 
  {
    renderSubscribers.push_back(RenderedObject);
  }

  void RenderObjects() {
    SDL_SetRenderDrawColor( mRenderer.get(), 0x00, 0xF0, 0x00, 0xFF );
    SDL_RenderClear(mRenderer.get());

    for (const auto &Object : renderSubscribers) {
      Object->RenderToScreen(mRenderer.get());
    }

    SDL_RenderPresent(mRenderer.get());
}

private:
  Window* mWindow;
  std::shared_ptr<SDL_Renderer> mRenderer;
  std::vector<LTexture*> renderSubscribers;
};
