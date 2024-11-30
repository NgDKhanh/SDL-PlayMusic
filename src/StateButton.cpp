#include "StateButton.h"

bool StateButton::HandleEvent(const SDL_Event* Event) {
    if (Event->type == SDL_MOUSEBUTTONDOWN &&
        Event->button.button == SDL_BUTTON_LEFT &&
        isHovered) 
    {
        (mStateFunc[mCurrentState])();

        if ((mCurrentState + 1) >= mNumberOfStates) {
            mCurrentState = 0;
        }
        else {
            mCurrentState++;
        }

        isClicked = true;
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

void StateButton::RenderToScreen(SDL_Renderer* renderer) {
    if (isClicked) {
        LoadTexture(mStateTexturePath[mCurrentState].c_str(), mApp->GetRenderer());
        isClicked = false;
    }
    SDL_RenderCopy(renderer, texture.get(), nullptr, &Rect);
}