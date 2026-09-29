#include "FacilitiesStaff.h"
#include <iostream>

FacilitiesStaff::FacilitiesStaff(CampusCoordinator* coord, const std::string& id,
                                 const std::string& base)
    : ResponseComponent(coord, id, base) {}

void FacilitiesStaff::deploy(const std::string& reason, const std::string& location) {
    std::cout << "    [FacilitiesStaff:" << unitID << "] Crew deployed to " << location
              << " — " << reason << std::endl;
    currentLocation = location;
    available = false;
}

void FacilitiesStaff::lockArea(const std::string& area) {
    std::cout << "    [FacilitiesStaff:" << unitID << "] Doors LOCKED: " << area << std::endl;
    triggerEvent("AREA_LOCKED:" + area);
}

void FacilitiesStaff::unlockArea(const std::string& area) {
    std::cout << "    [FacilitiesStaff:" << unitID << "] Doors UNLOCKED: " << area << std::endl;
    triggerEvent("AREA_UNLOCKED:" + area);
}

void FacilitiesStaff::receiveNotification(const std::string& event) {
    std::string detail;

    if (readEvent(event, "INCIDENT_ACTIVE:", detail)) {
        if (available) {
            deploy("opening emergency exits and shutting ventilation", detail);
        }
    } else if (readEvent(event, "INCIDENT_RESOLVED:", detail)) {
        if (isStationedAt(detail)) {
            standDown();
        }
    }
}
