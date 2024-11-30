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
#include <memory>
#include <map>

class StateButton : public EventReceiver, public LTexture {
public:
  // StateButton(Application* App, const int numberOfState, const char* imagePath[], void (*f[])(), int x, int y):
  //    isClicked(true), mCurrentState(0)
  // {
  //   mNumberOfStates = numberOfState;
  //   for (int i = 0; i < numberOfState; i++) {
  //     mStateFunc.push_back(f[i]);
  //     mStateTexturePath.push_back(imagePath[i]);
  //   }
  //   setPosition(x, y);

  //   mApp = App;
  //   // LoadTexture(imagePath[0], App->GetRenderer());
  //   // Update();
  // }

  StateButton(Application* App, const int numberOfState, const char* imagePath[], std::function<void()> f[], int x, int y) :
    isClicked(true), mCurrentState(0)
  {
    mNumberOfStates = numberOfState;
    for (int i = 0; i < numberOfState; i++) {
      if (f != nullptr) {
        mStateFunc.push_back(f[i]);
      }
      mStateTexturePath.push_back(imagePath[i]);
    }
    setPosition(x, y);

    mApp = App;
    // LoadTexture(imagePath[0], App->GetRenderer());
  }

  ~StateButton() {
    // SDL_DestroyTexture(texture.get());
  }

  void SetState(const uint8_t state) {
    mCurrentState = state;
    isClicked = true;
  }

  void AddFunction(const std::function<void()> func) {
    mStateFunc.push_back(func);
  }

  bool HandleEvent(const SDL_Event* Event) override;

  void RenderToScreen(SDL_Renderer* renderer) override;

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

    // Set the StateButton's dimensions to match the image size
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

private:
  void setPosition(int x = 50, int y = 50)
  {
    Rect.x = x;
    Rect.y = y;
  }

  Application *mApp;

  bool isClicked;
  bool isHovered { false };
  SDL_Rect Rect { 50, 50, 0, 0 }; // Width and height will be set based on the image size
  std::shared_ptr<SDL_Texture> texture { nullptr };
  // std::function<void()> func;

  uint8_t mNumberOfStates;
  uint8_t mCurrentState;
  // std::vector<std::string> mStateName; 
  // std::map<std::string, std::function<void()>> mStateFunc;
  // std::map<std::string, std::string> mStateTexturePath;
  std::vector<std::function<void()>> mStateFunc;
  std::vector<std::string> mStateTexturePath;
};
