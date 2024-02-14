#include "Button.h"

bool Button::HandleEvent(const SDL_Event* Event) {
    if (Event->type == SDL_MOUSEBUTTONDOWN &&
        Event->button.button == SDL_BUTTON_LEFT &&
        isHovered) 
    {
        // App->Quit();
        func();
    } 
    else if (
        Event->type == SDL_MOUSEMOTION) [[likely]]
        {
        if (isHovered != IsWithinBounds(
            Event->motion.x, Event->motion.y)) 
        {
            isHovered = !isHovered;
            Update();
        }
        return isHovered;
    }
    return false;
}