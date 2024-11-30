#pragma once
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <memory>
#include "Texture.h"
#include "Application.h"

class Horizontal_Bar : public LTexture
{
public:
    Horizontal_Bar(Application* App, const char* imagePath, int x, int y);

    void RenderToScreen(SDL_Renderer* renderer) override;

    void SetValue(int value)
    {
        if (Value <= MaxValue && Value >= MinValue)
            Value = value;
    }

    int GetHorizontal_BarHeght() const
    {
        return MaxValue;
    }

private:
    void LoadTexture(const char* imagePath, SDL_Renderer* renderer) 
    {
        // Load image and create texture
        SDL_Surface* loadedSurface = IMG_Load(imagePath);
        if (loadedSurface == nullptr) 
        {
            std::cerr << "Failed to load image! SDL_image Error: " << IMG_GetError() << std::endl;
            return;
        }

        texture = std::shared_ptr<SDL_Texture>(SDL_CreateTextureFromSurface(renderer, loadedSurface), SDL_DestroyTexture);
        
        if (texture == nullptr) 
        {
            std::cerr << "Failed to create texture! SDL Error: " << SDL_GetError() << std::endl;
            SDL_FreeSurface(loadedSurface);
            return;
        }

        // Set the button's dimensions to match the image size
        Rect.w = loadedSurface->w;
        Rect.h = loadedSurface->h;

        RectFill.w = Value;
        RectFill.h = loadedSurface->h;

        MinValue = 0;
        MaxValue = loadedSurface->w;

        // Cleanup loaded surface
        SDL_FreeSurface(loadedSurface);
    }

    void setPosition(int x = 0, int y = 0)
    {
        Rect.x = x;
        Rect.y = y;

        RectFill.x = 0;
        RectFill.y = 0;
    }

    void Update()
    {
        RectFill.h = Rect.x; 
        RectFill.y = Value;
    }

    int Value = 0;
    int MaxValue, MinValue;
    SDL_Rect Rect;
    SDL_Rect RectFill;
    std::shared_ptr<SDL_Texture> texture { nullptr };
};