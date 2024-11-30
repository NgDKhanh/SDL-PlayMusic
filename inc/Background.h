#pragma once
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "EventReceiver.h"
#include "Application.h"
#include "Texture.h"
#include <iostream>
#include <string>
#include <functional>
#include <memory>

class Background : public EventReceiver, public LTexture {
public:
  Background(Application* App, const char* imagePath) 
  {
    LoadTexture(imagePath, App->GetRenderer());
  }

  ~Background() {
    // SDL_DestroyTexture(texture.get());
  }

  void RenderToScreen(SDL_Renderer* renderer) override 
  {
    SDL_RenderCopy(renderer, texture.get(), nullptr, &Rect);
  }

protected:
  void LoadTexture(const char* imagePath, SDL_Renderer* renderer) {
    // Load image and create texture
    SDL_Surface* loadedSurface = IMG_Load(imagePath);
    if (loadedSurface == nullptr) {
      std::cerr << "Failed to load image! SDL_image Error: " << IMG_GetError() << std::endl;
      return;
    }

    texture = std::shared_ptr<SDL_Texture>(SDL_CreateTextureFromSurface(renderer, loadedSurface), SDL_DestroyTexture);
    if (texture == nullptr) {
      std::cerr << "Failed to create texture! SDL Error: " << SDL_GetError() << std::endl;
      SDL_FreeSurface(loadedSurface);
      return;
    }

    // Set the Background's dimensions to match the image size
    Rect.w = loadedSurface->w;
    Rect.h = loadedSurface->h;

    // Cleanup loaded surface
    SDL_FreeSurface(loadedSurface);
  }

private:
  bool isHovered { false };
  SDL_Rect Rect { 0, 0, 0, 0 }; // Width and height will be set based on the image size
  std::shared_ptr<SDL_Texture> texture { nullptr };
};
