#pragma once
#include "Text.h"
#include "DataControl.h"

class SongTitle : public BaseComponent, public Text {

public:
    SongTitle(Application* App, Mediator *Med, int x, int y, int size=25):
        BaseComponent(Med), Text(App, "", x, y, size) {
        }
};