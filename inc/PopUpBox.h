#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <string>
#include <memory>
#include "Application.h"
#include "Text.h"
#include "FrameControl.h"

class PopUpBox {
public:
    enum POP_UP_BOX_KIND : uint8_t {
        INFO = 0U,
        INPUT
    };

    PopUpBox(Application *app, POP_UP_BOX_KIND kind, uint16_t screenWidth_, uint16_t screenHeight_, 
        uint16_t width = 350, uint8_t height = 150) :
        mApp(app), mKind(kind), 
        screenHeight(screenHeight_), screenWidth(screenWidth_), popupWidth(width), popupHeight(height),
        mFont {std::shared_ptr<TTF_Font>(TTF_OpenFont("/usr/share/fonts/truetype/dejavu/DejaVuSans.ttf", 10), TTF_CloseFont)}
        {
            // Create a button
            if (kind == POP_UP_BOX_KIND::INPUT) {
                // Text box dimensions
                textBoxRect = { popupX + 20, popupY + 50, popupWidth - 40, 40 };
                buttonOKRect = { popupX + popupWidth / 2 - 150, popupY + popupHeight - 40, 100, 30 }; // Centered button
                buttonCancelRect = { popupX + popupWidth / 2 + 30, popupY + popupHeight - 40, 100, 30 }; // Centered button
            }
            else if (kind == POP_UP_BOX_KIND::INFO) {
                buttonOKRect = { popupX + popupWidth / 2 - 50, popupY + popupHeight - 40, 100, 30 }; // Centered button
            }
        }

    std::string showPopUp(std::string message);

    // Function to render text on the screen
    void renderText(const std::string& text, int x, int y, SDL_Color textColor) {
        SDL_Surface* newSurface = TTF_RenderUTF8_Blended(
            mFont.get(), text.c_str(), textColor
        );
        if (newSurface == nullptr) {
            std::cerr << "Failed to load text! SDL_TTF Error: " << TTF_GetError() << std::endl;
            return;
        }

        std::shared_ptr<SDL_Texture> TextTexture = std::shared_ptr<SDL_Texture>(SDL_CreateTextureFromSurface(mApp->GetRenderer(), newSurface), SDL_DestroyTexture);

        if (TextTexture == nullptr) {
            std::cerr << "Failed to create texture! SDL Error: " << SDL_GetError() << std::endl;
            SDL_FreeSurface(newSurface);
            return;
        }

        SDL_Rect dstRect = { x, y, newSurface->w, newSurface->h };
        // Cleanup loaded surface
        SDL_FreeSurface(newSurface);
        SDL_RenderCopy(mApp->GetRenderer(), TextTexture.get(), nullptr, &dstRect);
    }

private:
    Application *mApp;
    std::shared_ptr<TTF_Font> mFont { nullptr };
    POP_UP_BOX_KIND mKind;

    // Popup box dimensions
    uint16_t popupWidth = 350;
    uint16_t popupHeight = 150;
    uint16_t screenWidth = 640; // Adjust based on your screen size
    uint16_t screenHeight = 480; // Adjust based on your screen size
    uint16_t popupX = (screenWidth - popupWidth) / 2;
    uint16_t popupY = (screenHeight - popupHeight) / 2;

    // Background color for popup
    SDL_Color popupBgColor = { 50, 50, 50, 255 }; // Dark gray
    SDL_Color textColor = { 255, 255, 255, 255 }; // White
    SDL_Color textInsideTextBoxColor = { 0, 0, 0, 255 }; // White
    SDL_Color textBoxColor = { 255, 255, 255, 255 }; // White text box
    SDL_Color textBoxBorderColor = { 200, 200, 200, 255 }; // Light gray border

    bool buttonOKClicked = false;
    bool buttonCancelClicked = false;

    std::string inputText = ""; // Text entered by the user

    // Text box dimensions
    SDL_Rect textBoxRect;

    // Create a button
    SDL_Rect buttonOKRect;
    SDL_Rect buttonCancelRect;
};