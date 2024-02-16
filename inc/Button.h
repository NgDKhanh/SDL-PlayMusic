//   void Update() {
//     auto [r, g, b, a] { isHovered ? HoverColor : BGColor };
//     SDL_FillRect(
//       SDLWindowSurface,
//       &Rect,
//       SDL_MapRGB(SDLWindowSurface->format, r, g, b)
//     );
//   }

#pragma once
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "EventReceiver.h"
#include "Application.h"
#include "Texture.h"
#include <iostream>
#include <string>
#include <functional>

class Button : public EventReceiver, public LTexture {
public:
  Button(Application* App, const char* imagePath, void (*f)(), int x, int y) 
    // :App{App}
  {
    func = f;
    setPosition(x, y);
    LoadTexture(imagePath, App->GetRenderer());
    // Update();
  }

  Button(Application* App, const char* imagePath, std::function<void()> f, int x, int y) 
    // :App{App}
  {
    func = f;
    setPosition(x, y);
    LoadTexture(imagePath, App->GetRenderer());
    // Update();
  }

  ~Button() {
    SDL_DestroyTexture(texture);
  }

  bool HandleEvent(const SDL_Event* Event) override;

  void RenderToScreen(SDL_Renderer* renderer) override 
  {
    // Update();
    SDL_RenderCopy(renderer, texture, nullptr, &Rect);
  }

private:
  void LoadTexture(const char* imagePath, SDL_Renderer* renderer) {
    // Load image and create texture
    SDL_Surface* loadedSurface = IMG_Load(imagePath);
    if (loadedSurface == nullptr) {
      std::cerr << "Failed to load image! SDL_image Error: " << IMG_GetError() << std::endl;
      return;
    }

    texture = SDL_CreateTextureFromSurface(renderer, loadedSurface);
    if (texture == nullptr) {
      std::cerr << "Failed to create texture! SDL Error: " << SDL_GetError() << std::endl;
      SDL_FreeSurface(loadedSurface);
      return;
    }

    // Set the button's dimensions to match the image size
    Rect.w = loadedSurface->w;
    Rect.h = loadedSurface->h;

    // Cleanup loaded surface
    SDL_FreeSurface(loadedSurface);
  }

  bool IsWithinBounds(int x, int y) {
    // Too far left
    if (x < Rect.x) return false;

    // Too far right
    if (x > Rect.x + Rect.w) return false;

    // Too high
    if (y < Rect.y) return false;

    // Too low
    if (y > Rect.y + Rect.h) return false;

    // Inside rectangle
    return true;
  }

  // void Update() {
  //   SDL_RenderCopy(App->GetRenderer(), texture, nullptr, &Rect);
  // }

  void setPosition(int x = 50, int y = 50)
  {
    Rect.x = x;
    Rect.y = y;
  }

  bool isHovered { false };
  SDL_Rect Rect { 50, 50, 0, 0 }; // Width and height will be set based on the image size
  // Application* App { nullptr };
  SDL_Texture* texture { nullptr };
  std::function<void()> func;
};
