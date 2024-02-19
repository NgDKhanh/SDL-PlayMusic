#include "Bar.h"

Bar::Bar(Application* App, const char* imagePath, int x, int y) 
{
    LoadTexture(imagePath, App->GetRenderer());
    setPosition(x, y);
}

void Bar::RenderToScreen(SDL_Renderer* renderer) 
{
    Update();
    // SDL_RenderClear(renderer);
    SDL_RenderCopy(renderer, texture.get(), nullptr, &Rect);
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderFillRect(renderer, &RectFill);
    // SDL_SetRenderDrawColor( renderer, 0xFF, 0xFF, 0xFF, 0xFF );
}