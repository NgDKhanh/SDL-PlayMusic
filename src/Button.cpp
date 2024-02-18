#include "Button.h"

bool Button::HandleEvent(const SDL_Event* Event) {
    if (Event->type == SDL_MOUSEBUTTONDOWN &&
        Event->button.button == SDL_BUTTON_LEFT &&
        isHovered) 
    {
        func();
    } 
    else if (
        Event->type == SDL_MOUSEMOTION)
        {
        if (isHovered != IsWithinBounds(
            Event->motion.x, Event->motion.y)) 
        {
            isHovered = !isHovered;
        }
        return isHovered;
    }
    return false;
}