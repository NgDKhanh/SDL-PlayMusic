#include "Application.h"

void Application::Quit()
{
    SDL_Event QuitEvent { SDL_QUIT };
    SDL_PushEvent(&QuitEvent);
}