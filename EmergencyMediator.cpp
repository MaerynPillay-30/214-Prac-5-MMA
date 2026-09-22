#include "EmergencyMediator.h"
#include "ResponseComponent.h"
#include <iostream>

EmergencyMediator::EmergencyMediator() {}

void EmergencyMediator::registerComponent(ResponseComponent* component) {
    components.push_back(component);
    std::cout << "  [Mediator] Component registered: " << component->getUnitID() << std::endl;
}

void EmergencyMediator::notify(ResponseComponent* sender, const std::string& event) {
    if (sender) {
        std::cout << "  [Mediator] Event \"" << event << "\" received from "
                  << sender->getUnitID() << " -> coordinating response." << std::endl;
    } else {
        std::cout << "  [Mediator] Event \"" << event
                  << "\" (command-initiated) -> coordinating response." << std::endl;
    }
    // Coordinate: relay event to all other registered colleagues
    for (auto* comp : components) {
        if (comp != sender) {
            comp->receiveNotification(event);
        }
    }
}

void EmergencyMediator::broadcastToAll(const std::string& event) {
    std::cout << "  [Mediator] Broadcasting \"" << event << "\" to ALL components." << std::endl;
    for (auto* comp : components) {
        comp->receiveNotification(event);
    }
}

std::string EmergencyMediator::getComponentStatus(const std::string& unitID) {
    for (auto* comp : components) {
        if (comp->getUnitID() == unitID) {
            comp->getStatus();
            return unitID;
        }
    }
    std::cout << "  [Mediator] WARNING: Unit \"" << unitID << "\" not found in registry." << std::endl;
    return "NOT_FOUND";
}
