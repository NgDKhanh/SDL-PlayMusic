#pragma once
#include <iostream>
#include <string>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <memory>
#include "Application.h"
#include "Texture.h"

class Text : public LTexture {

public:
    Text(Application *App, std::string Content, int x, int y, int Size = 25) :
    mApp(App), mContent(Content), changeText(false), 
    Font {std::shared_ptr<TTF_Font>(TTF_OpenFont("/usr/share/fonts/truetype/dejavu/DejaVuSans.ttf", Size), TTF_CloseFont)}
    {
        if (!Font) {
            std::cout << "Error loading font:" << SDL_GetError();
        }
        SetPosition(x, y);
    }

    void SetFontSize(int NewSize);

    virtual void RenderToScreen(SDL_Renderer* renderer) override;

    ~Text() {
        // if (TTF_WasInit()) {
        //     TTF_CloseFont(Font.get());
        // }
    }

    void SetText(std::string Content);

    Text(const Text&) = delete;
    Text& operator=(const Text&) = delete;

private:
    void SetPosition(int x, int y) {
        mPosition.x = x;
        mPosition.y = y;
    }

    void CreateSurface(std::string Content, SDL_Renderer* renderer) {
        SDL_Surface* newSurface = TTF_RenderUTF8_Blended(
            Font.get(), Content.c_str(), {0, 0, 0}
        );
        if (newSurface == nullptr) {
            std::cerr << "Failed to load text! SDL_TTF Error: " << TTF_GetError() << std::endl;
            return;
        }

        TextTexture = std::shared_ptr<SDL_Texture>(SDL_CreateTextureFromSurface(renderer, newSurface), SDL_DestroyTexture);

        if (TextTexture == nullptr) {
            std::cerr << "Failed to create texture! SDL Error: " << SDL_GetError() << std::endl;
            SDL_FreeSurface(newSurface);
            return;
        }

        // Set the text's dimensions to match the image size
        Rect.w = newSurface->w;
        Rect.h = newSurface->h;

        Rect.x = mPosition.x - (Rect.w / 2);
        Rect.y = mPosition.y;

        // Cleanup loaded surface
        SDL_FreeSurface(newSurface);
    }

    Application *mApp;
    std::string mContent;
    bool changeText;
    struct Position {
        float x;
        float y;
    } mPosition;
    SDL_Rect Rect { 0, 0, 0, 0 }; // Width and height will be set base
    std::shared_ptr<TTF_Font> Font { nullptr };
    std::shared_ptr<SDL_Texture> TextTexture { nullptr };
    SDL_Rect DestinationRectangle{0, 0, 0, 0};
};
