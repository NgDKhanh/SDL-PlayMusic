#pragma once

#include "Horizontal_Bar.h"
#include "DataControl.h"

class TimeBar : public Horizontal_Bar, public BaseComponent {
    
public:
    TimeBar(Application* App, Mediator *Med, const char* imagePath, int x, int y):
        Horizontal_Bar(App, imagePath, x, y), BaseComponent(Med) {
            // StateButton::AddFunction([Med]() {Med->Notify(this, "Play");});
        }

};