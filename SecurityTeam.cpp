#include "SecurityTeam.h"
#include <iostream>

SecurityTeam::SecurityTeam(CampusCoordinator* coord,
                           const std::string& id,
                           const std::string& loc)
    : ResponseComponent(coord, id, loc) {}

void SecurityTeam::deploy(const std::string& desc, const std::string& loc) {
    std::cout << "    [SecurityTeam:" << unitID << "] Deploying to " << loc
              << " — " << desc << std::endl;
    currentLocation = loc;
    isAvailable = false;
    triggerEvent("SECURITY_DEPLOYED:" + loc);
}

void SecurityTeam::dispatchTeam(const std::string& location) {
    std::cout << "    [SecurityTeam:" << unitID << "] Team dispatched to " << location << std::endl;
    currentLocation = location;
    isAvailable = false;
}

void SecurityTeam::requestBackup() {
    std::cout << "    [SecurityTeam:" << unitID << "] BACKUP REQUESTED!" << std::endl;
    triggerEvent("BACKUP_REQUESTED");
}

void SecurityTeam::reportStatus() {
    std::cout << "    [SecurityTeam:" << unitID << "] Status: location=" << currentLocation
              << ", available=" << (isAvailable ? "YES" : "NO") << std::endl;
}

void SecurityTeam::detainSuspect() {
    std::cout << "    [SecurityTeam:" << unitID << "] Suspect detained at " << currentLocation << std::endl;
}

void SecurityTeam::escalateLevel() {
    std::cout << "    [SecurityTeam:" << unitID << "] Security level escalated." << std::endl;
    triggerEvent("SECURITY_ESCALATED");
}

void SecurityTeam::getStatus() {
    reportStatus();
}

void SecurityTeam::receiveNotification(const std::string& event) {
    std::cout << "    [SecurityTeam:" << unitID << "] << Notification: \"" << event << "\"" << std::endl;
    // React intelligently to specific events
    if (event.find("DISPATCH:") == 0) {
        std::string location = event.substr(9);
        dispatchTeam(location);
    } else if (event == "EVACUATE_NOW" || event == "CHEMICAL_SPILL") {
        std::cout << "    [SecurityTeam:" << unitID << "] Assisting with evacuation perimeter." << std::endl;
    }
}
