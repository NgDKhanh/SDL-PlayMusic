#include "StaticButton.h"

void StaticButton::Init() {
    Button::SetFunction([this]() {mediator_->Notify(this, mMessage);});
}