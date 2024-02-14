 #include "Window.h"
 
Window::Window()
{
  SDL_Init(SDL_INIT_VIDEO);

  SDLWindow = SDL_CreateWindow(
    "Hello Window", 0, 0, 640, 480, 0
  );

  SDLWindowSurface = SDL_GetWindowSurface(SDLWindow);

  SDL_FillRect(
    SDLWindowSurface,
    nullptr,
    SDL_MapRGB(SDLWindowSurface->format, 40, 40, 40)
  );
}

Window::Window(const char *title,
                int x, int y, int w,
                int h, Uint32 flags,
                Uint8 r, Uint8 g, Uint8 b)
{
  SDL_Init(SDL_INIT_VIDEO);

  SDLWindow = SDL_CreateWindow(
    title, x, y, w, h, flags
  );

  SDLWindowSurface = SDL_GetWindowSurface(SDLWindow);

  SDL_FillRect(
    SDLWindowSurface,
    nullptr,
    SDL_MapRGB(SDLWindowSurface->format, r, g, b)
  );
}

Window::Window(std::string title, Uint32 flags)
{
  SDL_Init(SDL_INIT_VIDEO);

    SDLWindow = SDL_CreateWindow(
      title.c_str(),
      SDL_WINDOWPOS_UNDEFINED,
      SDL_WINDOWPOS_UNDEFINED,
      windowWidth, windowHeight, flags
    );

    SDLWindowSurface = SDL_GetWindowSurface(SDLWindow);
}

void Window::RenderFrame()
{
  SDL_UpdateWindowSurface(SDLWindow);
}

void Window::Update()
{
  SDL_FillRect(
    SDLWindowSurface,
    nullptr,
    SDL_MapRGB(
      SDLWindowSurface->format,
      bgRed, bgGreen, bgBlue
    )
  );
}

void Window::SetBackgroundColor(int R, int G, int B) 
{
  bgRed = R;
  bgGreen = G;
  bgBlue = B;
}

void Window::SetTitle(std::string NewTitle) 
{
  SDL_SetWindowTitle(
    SDLWindow, NewTitle.c_str()
  );
}

void Window::ChangeWindowSize(int Amount) 
{
  SDL_SetWindowSize(
    SDLWindow,
    windowWidth += Amount,
    windowHeight += Amount
  );
}

int Window::MoveRelative(int x, int y) 
{
  int CurrentX; int CurrentY;
  SDL_GetWindowPosition(
    SDLWindow, &CurrentX, &CurrentY
  );

  SDL_SetWindowPosition(
    SDLWindow, CurrentX + x, CurrentY + y
  );
}