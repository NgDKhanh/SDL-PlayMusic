#include "PopUpBox.h"

std::string PopUpBox::showPopUp(std::string message) {
    bool popupActive = true;

    while (popupActive) {
        SDL_Event event;
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                popupActive = false;
                break;
            } else if (event.type == SDL_MOUSEBUTTONDOWN) {
                int mouseX = event.button.x;
                int mouseY = event.button.y;

                // Check if the mouse clicked on the button
                if (mouseX >= buttonOKRect.x && mouseX <= buttonOKRect.x + buttonOKRect.w &&
                    mouseY >= buttonOKRect.y && mouseY <= buttonOKRect.y + buttonOKRect.h) {
                    buttonCancelClicked = false;
                    buttonOKClicked = true;
                    popupActive = false;
                }
                else if (mouseX >= buttonCancelRect.x && mouseX <= buttonCancelRect.x + buttonCancelRect.w &&
                    mouseY >= buttonCancelRect.y && mouseY <= buttonCancelRect.y + buttonCancelRect.h) {
                    buttonCancelClicked = true;
                    buttonOKClicked = false;
                    popupActive = false;
                } 
            }
            else if (event.type == SDL_TEXTINPUT) {
                // Append the entered character to the input text
                inputText += event.text.text;
            } else if (event.type == SDL_KEYDOWN) {
                // Handle backspace
                if (event.key.keysym.sym == SDLK_BACKSPACE && !inputText.empty()) {
                    inputText.pop_back();
                } else if (event.key.keysym.sym == SDLK_RETURN) {
                    buttonOKClicked = true;
                    popupActive = false; // Close the popup when Enter is pressed
                }
            }
        }

        // Clear the mRenderer
        SDL_SetRenderDrawColor(mApp->GetRenderer(), 0, 0, 0, 255); // Black background
        SDL_RenderClear(mApp->GetRenderer());

        // Draw the popup background
        SDL_SetRenderDrawColor(mApp->GetRenderer(), popupBgColor.r, popupBgColor.g, popupBgColor.b, popupBgColor.a);
        SDL_Rect popupRect = { popupX, popupY, popupWidth, popupHeight };
        SDL_RenderFillRect(mApp->GetRenderer(), &popupRect);

        // Draw the message text
        renderText(message, popupX + 20, popupY + 20, textColor);

        // Draw the text box
        SDL_SetRenderDrawColor(mApp->GetRenderer(), textBoxColor.r, textBoxColor.g, textBoxColor.b, textBoxColor.a);
        SDL_RenderFillRect(mApp->GetRenderer(), &textBoxRect);
        SDL_SetRenderDrawColor(mApp->GetRenderer(), textBoxBorderColor.r, textBoxBorderColor.g, textBoxBorderColor.b, textBoxBorderColor.a);
        SDL_RenderDrawRect(mApp->GetRenderer(), &textBoxRect);

        // Draw the entered text
        if (!inputText.empty()) {
            renderText(inputText, textBoxRect.x + 5, textBoxRect.y + 10, textInsideTextBoxColor);
        } else {
            // Optionally, render a placeholder or skip rendering
            renderText(" ", textBoxRect.x + 5, textBoxRect.y + 10, textInsideTextBoxColor);
        }


        // Draw the OK button
        SDL_SetRenderDrawColor(mApp->GetRenderer(), 0, 200, 0, 255); // Green button
        SDL_RenderFillRect(mApp->GetRenderer(), &buttonOKRect);
        renderText("OK", buttonOKRect.x + 35, buttonOKRect.y + 5, textColor);

        // Draw the Cancel button
        SDL_SetRenderDrawColor(mApp->GetRenderer(), 200, 0, 0, 255); // Red button
        SDL_RenderFillRect(mApp->GetRenderer(), &buttonCancelRect);
        renderText("Cancel", buttonCancelRect.x + 20, buttonCancelRect.y + 5, textColor);

        // Update the screen
        SDL_RenderPresent(mApp->GetRenderer());
    }

    if (buttonOKClicked) {
        return inputText;
    }
    else {
        return "Default";
    }
}