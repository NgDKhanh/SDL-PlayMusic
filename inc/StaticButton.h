#pragma once

#include "Button.h"
#include "DataControl.h"

class StaticButton : public Button, public BaseComponent {
    
public:
    StaticButton(Application* App, Mediator *Med, const char* imagePath, int x, int y, std::string message):
        Button(App, imagePath, nullptr, x, y), BaseComponent(Med), mMessage(message) {
        }

    void Init();

private:
    std::string mMessage;
};