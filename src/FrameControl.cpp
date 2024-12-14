#include "FrameControl.h"

uint16_t FPS;
int frameDelay = 0;
uint32_t frameStart = 0;
int frameTime = 0;

void SetFPS(uint16_t fps) {
    FPS = fps;
    frameDelay = 1000/fps;
}

void GetFrameStart(uint32_t currentTick) {
    frameStart = currentTick;
}

void FrameDelayControl() {
    // Limit frame rate
    frameTime = SDL_GetTicks() - frameStart;
    if (frameDelay > frameTime) {
        SDL_Delay(frameDelay - frameTime);
    }
}