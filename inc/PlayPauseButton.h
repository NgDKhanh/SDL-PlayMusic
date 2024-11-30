#pragma once

#include "StateButton.h"
#include "DataControl.h"

class PlayPauseButton : public StateButton, public BaseComponent {
    
public:
    enum PlayingMode : uint8_t {
        PLAY = 0U,
        PAUSE
    };

    PlayPauseButton(Application* App, Mediator *Med, const int numberOfState, const char* imagePath[], int x, int y):
        StateButton(App, numberOfState, imagePath, nullptr, x, y), BaseComponent(Med) {
            // StateButton::AddFunction([Med]() {Med->Notify(this, "Play");});
        }

    void Init();
};