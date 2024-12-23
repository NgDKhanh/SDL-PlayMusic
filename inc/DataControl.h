#pragma once

#include <iostream>
#include <string>
#include <memory>

class BaseComponent;

class Mediator {

public:
    virtual void Notify(BaseComponent *sender, std::string event) const = 0;
};

class BaseComponent {
protected:
    Mediator* mediator_;
public:
    BaseComponent(Mediator *mediator = nullptr) : mediator_(mediator) {}

    void set_mediator(Mediator *mediator) {
        this->mediator_ = mediator;
    }

    // virtual void handle_notify() = 0;
};