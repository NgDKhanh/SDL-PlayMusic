#include "Text.h"

void Text::SetFontSize(int NewSize) {
    TTF_SetFontSize(Font.get(), NewSize);
}

void Text::RenderToScreen(SDL_Renderer* renderer) {
    if (changeText) {
        CreateSurface(mContent, mApp->GetRenderer());
        changeText = false;
    }

    SDL_RenderCopy(renderer, TextTexture.get(), nullptr, &Rect);
}

void Text::SetText(std::string Content) {
    if (Content.size() > 0) {
        mContent = Content;
    }
    else {
        mContent = "None";
    }
    changeText = true;
}