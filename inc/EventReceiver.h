#pragma once
#include <SDL2/SDL.h>

class EventReceiver {
public:
  virtual bool HandleEvent(const SDL_Event* Event);
};