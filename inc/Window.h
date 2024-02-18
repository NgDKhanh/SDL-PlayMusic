// Window.h
#pragma once
#include <SDL2/SDL.h>
#include <string>
#include <memory>

class Window {
public:
  Window();
  
  Window(const char *title,
          int x, int y, int w,
          int h, Uint32 flags, 
          Uint8 r, Uint8 g, Uint8 b);

  Window(std::string title, Uint32 flags);

  void RenderFrame();

  void Update();

  void SetBackgroundColor(int R, int G, int B);

  void SetTitle(std::string NewTitle);

  void ChangeWindowSize(int Amount);

  int MoveRelative(int x, int y);

  int GetWindowWidth() const {
    return windowWidth;
  }

  int GetWindowHeight() const {
    return windowHeight;
  }

  SDL_Surface* GetSurface() {
    return SDLWindowSurface.get();
  }

  void GrabMouse() {
    SDL_SetWindowMouseGrab(SDLWindow.get(), SDL_TRUE);
  }

  void FreeMouse() {
    SDL_SetWindowMouseGrab(SDLWindow.get(), SDL_FALSE);
  }

  SDL_Window* GetSDLWindow() const
  {
    return SDLWindow.get();
  }

private:
  std::shared_ptr<SDL_Window> SDLWindow { nullptr };
  std::shared_ptr<SDL_Surface> SDLWindowSurface { nullptr };

  int windowWidth { 640 };
  int windowHeight { 480 };

  int bgRed { 40 };
  int bgGreen { 40 };
  int bgBlue { 40 };
};