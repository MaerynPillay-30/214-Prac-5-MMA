#include "ResponseComponent.h"
#include "CampusCoordinator.h"
#include <iostream>

ResponseComponent::ResponseComponent(CampusCoordinator* coord,
                                     const std::string& id,
                                     const std::string& base)
    : unitID(id), baseLocation(base), currentLocation(base),
      available(true), coordinator(coord) {}

void ResponseComponent::triggerEvent(const std::string& event) {
    if (coordinator != nullptr) {
        coordinator->notify(this, event);
    }
}

bool ResponseComponent::isStationedAt(const std::string& area) const {
    return !available && currentLocation.compare(0, area.size(), area) == 0;
}

bool ResponseComponent::readEvent(const std::string& event, const std::string& prefix,
                                  std::string& detail) {
    if (event.compare(0, prefix.size(), prefix) != 0) {
        return false;
    }
    detail = event.substr(prefix.size());
    return true;
}

void ResponseComponent::standDown() {
    std::cout << "    [" << unitID << "] Standing down, returning to "
              << baseLocation << std::endl;
    currentLocation = baseLocation;
    available = true;
}

void ResponseComponent::getStatus() const {
    std::cout << "    [" << unitID << "] at " << currentLocation << " — "
              << (available ? "AVAILABLE" : "COMMITTED") << std::endl;
}

bool ResponseComponent::isAvailable() const {
    return available;
}

std::string ResponseComponent::getUnitID() const {
    return unitID;
}
