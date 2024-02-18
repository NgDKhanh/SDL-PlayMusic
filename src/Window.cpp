 #include "Window.h"
 
Window::Window()
{
  SDL_Init(SDL_INIT_VIDEO);

  SDLWindow = std::shared_ptr<SDL_Window>(SDL_CreateWindow(
    "Hello Window", 0, 0, 640, 480, 0
  ), SDL_DestroyWindow);

  SDLWindowSurface = std::shared_ptr<SDL_Surface>(SDL_GetWindowSurface(SDLWindow.get()), SDL_FreeSurface);

  SDL_FillRect(
    SDLWindowSurface.get(),
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

  SDLWindow = std::shared_ptr<SDL_Window>(SDL_CreateWindow(
    title, x, y, w, h, flags
  ), SDL_DestroyWindow);

  SDLWindowSurface = std::shared_ptr<SDL_Surface>(SDL_GetWindowSurface(SDLWindow.get()), SDL_FreeSurface);

  SDL_FillRect(
    SDLWindowSurface.get(),
    nullptr,
    SDL_MapRGB(SDLWindowSurface->format, r, g, b)
  );
}

Window::Window(std::string title, Uint32 flags)
{
  SDL_Init(SDL_INIT_VIDEO);

  SDLWindow = std::shared_ptr<SDL_Window>(SDL_CreateWindow(
      title.c_str(),
      SDL_WINDOWPOS_UNDEFINED,
      SDL_WINDOWPOS_UNDEFINED,
      windowWidth, windowHeight, flags
  ), SDL_DestroyWindow);

  SDLWindowSurface = std::shared_ptr<SDL_Surface>(SDL_GetWindowSurface(SDLWindow.get()), SDL_FreeSurface);
}

void Window::RenderFrame()
{
  SDL_UpdateWindowSurface(SDLWindow.get());
}

void Window::Update()
{
  SDL_FillRect(
    SDLWindowSurface.get(),
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
    SDLWindow.get(), NewTitle.c_str()
  );
}

void Window::ChangeWindowSize(int Amount) 
{
  SDL_SetWindowSize(
    SDLWindow.get(),
    windowWidth += Amount,
    windowHeight += Amount
  );
}

int Window::MoveRelative(int x, int y) 
{
  int CurrentX; int CurrentY;
  SDL_GetWindowPosition(
    SDLWindow.get(), &CurrentX, &CurrentY
  );

  SDL_SetWindowPosition(
    SDLWindow.get(), CurrentX + x, CurrentY + y
  );
}