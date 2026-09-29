#include "EmergencyMediator.h"
#include "ResponseComponent.h"
#include <iostream>

EmergencyMediator::EmergencyMediator() {}

EmergencyMediator::~EmergencyMediator() {
    // The mediator owns every registered unit.
    for (std::size_t i = 0; i < components.size(); ++i) {
        delete components[i];
    }
    components.clear();
}

ResponseComponent* EmergencyMediator::findUnit(const std::string& unitID) const {
    for (std::size_t i = 0; i < components.size(); ++i) {
        if (components[i]->getUnitID() == unitID) {
            return components[i];
        }
    }
    return nullptr;
}

void EmergencyMediator::registerComponent(ResponseComponent* component) {
    if (component == nullptr) {
        return;
    }
    components.push_back(component);
    std::cout << "  [Mediator] Registered unit " << component->getUnitID()
              << " (" << components.size() << " units on the network)" << std::endl;
}

// A unit raised an event: relay it to every OTHER unit.
void EmergencyMediator::notify(ResponseComponent* sender, const std::string& event) {
    if (sender == nullptr) {
        broadcast(event);
        return;
    }
    std::cout << "  [Mediator] " << sender->getUnitID() << " raised \"" << event
              << "\" -> relaying to the other units" << std::endl;
    for (std::size_t i = 0; i < components.size(); ++i) {
        if (components[i] != sender) {
            components[i]->receiveNotification(event);
        }
    }
}

// A request from outside the unit group (incident, facade): send to all units.
void EmergencyMediator::broadcast(const std::string& event) {
    std::cout << "  [Mediator] Broadcasting \"" << event << "\" to all "
              << components.size() << " units" << std::endl;
    for (std::size_t i = 0; i < components.size(); ++i) {
        components[i]->receiveNotification(event);
    }
}

bool EmergencyMediator::dispatchUnit(const std::string& unitID,
                                     const std::string& location,
                                     const std::string& reason) {
    ResponseComponent* unit = findUnit(unitID);
    if (unit == nullptr) {
        std::cout << "  [Mediator] ERROR: No unit with ID \"" << unitID
                  << "\" is registered. Dispatch refused." << std::endl;
        return false;
    }
    if (!unit->isAvailable()) {
        std::cout << "  [Mediator] ERROR: " << unitID
                  << " is already committed to another task. Dispatch refused." << std::endl;
        return false;
    }
    std::cout << "  [Mediator] Dispatching " << unitID << " to " << location << std::endl;
    unit->deploy(reason, location);
    return true;
}

void EmergencyMediator::recallUnit(const std::string& unitID) {
    ResponseComponent* unit = findUnit(unitID);
    if (unit == nullptr) {
        std::cout << "  [Mediator] ERROR: Cannot recall unknown unit \"" << unitID << "\"." << std::endl;
        return;
    }
    std::cout << "  [Mediator] Recalling " << unitID << std::endl;
    unit->standDown();
}

void EmergencyMediator::printRoster() const {
    std::cout << "\n  [Mediator] ---------- UNIT ROSTER ----------" << std::endl;
    for (std::size_t i = 0; i < components.size(); ++i) {
        components[i]->getStatus();
    }
    std::cout << "  [Mediator] -----------------------------------\n" << std::endl;
}
