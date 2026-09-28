#include "MedicalResponder.h"
#include <iostream>

MedicalResponder::MedicalResponder(CampusCoordinator* coord, const std::string& id,
                                   const std::string& base)
    : ResponseComponent(coord, id, base) {}

void MedicalResponder::deploy(const std::string& reason, const std::string& location) {
    std::cout << "    [MedicalResponder:" << unitID << "] Ambulance crew deployed to "
              << location << " — " << reason << std::endl;
    currentLocation = location;
    available = false;
}

void MedicalResponder::receiveNotification(const std::string& event) {
    std::string detail;

    if (readEvent(event, "HAZMAT:", detail)) {
        if (available) {
            deploy("HAZMAT casualty triage", detail);
        }
    } else if (readEvent(event, "INCIDENT_RESOLVED:", detail)) {
        if (isStationedAt(detail)) {
            standDown();
        }
    }
}
