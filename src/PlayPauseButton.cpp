#include "PlayPauseButton.h"

void PlayPauseButton::Init() {
    StateButton::AddFunction([this]() {mediator_->Notify(this, "Play");});
    StateButton::AddFunction([this]() {mediator_->Notify(this, "Pause");});
}