#include "Layer.h"

bool Layer::HandleEvent(const SDL_Event* Event) {
    for (const auto &Handler : Subscribers) {
        if (Handler->HandleEvent(Event)) {
        return true;
        }
    }
    return false;
}

void Layer::SubscribeToEvents(EventReceiver* Receiver) {
    Subscribers.push_back(std::shared_ptr<EventReceiver>(Receiver));
}