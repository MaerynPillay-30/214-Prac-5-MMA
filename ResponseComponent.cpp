#include "ResponseComponent.h"
#include <iostream>

ResponseComponent::ResponseComponent(CampusCoordinator* coord,
                                     const std::string& id,
                                     const std::string& loc)
    : isAvailable(true), currentLocation(loc), unitID(id), coordinator(coord) {
    // Self-register with the mediator upon construction
    coordinator->registerComponent(this);
}

void ResponseComponent::triggerEvent(const std::string& event) {
    if (coordinator) {
        coordinator->notify(this, event);
    }
}

void ResponseComponent::setAvailable(bool b) {
    isAvailable = b;
}

std::string ResponseComponent::getUnitID() {
    return unitID;
}
