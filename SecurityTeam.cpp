#include "SecurityTeam.h"
#include <iostream>

SecurityTeam::SecurityTeam(CampusCoordinator* coord, const std::string& id,
                           const std::string& base)
    : ResponseComponent(coord, id, base) {}

void SecurityTeam::deploy(const std::string& reason, const std::string& location) {
    std::cout << "    [SecurityTeam:" << unitID << "] Team deployed to " << location
              << " — " << reason << std::endl;
    currentLocation = location;
    available = false;
}

void SecurityTeam::receiveNotification(const std::string& event) {
    std::string detail;

    if (readEvent(event, "AREA_LOCKED:", detail)) {
        if (available) {
            deploy("securing the perimeter of the locked area", detail);
        } else {
            std::cout << "    [SecurityTeam:" << unitID << "] Already committed at "
                      << currentLocation << " — cannot cover " << detail << std::endl;
        }
    } else if (readEvent(event, "AREA_UNLOCKED:", detail)) {
        if (isStationedAt(detail)) {
            std::cout << "    [SecurityTeam:" << unitID << "] Lockdown lifted at "
                      << detail << std::endl;
            standDown();
        }
    } else if (readEvent(event, "INCIDENT_RESOLVED:", detail)) {
        if (isStationedAt(detail)) {
            standDown();
        }
    }
}
