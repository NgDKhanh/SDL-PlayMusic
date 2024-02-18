#pragma once
#include <vector>
#include <SDL2/SDL.h>
#include <memory>
#include "EventReceiver.h"

class Layer {
public:
  bool HandleEvent(const SDL_Event* Event);

  void SubscribeToEvents(EventReceiver* Receiver);

private:
  std::vector<std::shared_ptr<EventReceiver>> Subscribers;
};