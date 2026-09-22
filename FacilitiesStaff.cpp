#include "FacilitiesStaff.h"
#include <iostream>

FacilitiesStaff::FacilitiesStaff(CampusCoordinator* coord,
                                 const std::string& id,
                                 const std::string& loc)
    : ResponseComponent(coord, id, loc) {}

void FacilitiesStaff::deploy(const std::string& desc, const std::string& loc) {
    std::cout << "    [FacilitiesStaff:" << unitID << "] Deploying to " << loc
              << " — " << desc << std::endl;
    currentLocation = loc;
    isAvailable = false;
    triggerEvent("FACILITIES_DEPLOYED:" + loc);
}

void FacilitiesStaff::lockArea(const std::string& area) {
    std::cout << "    [FacilitiesStaff:" << unitID << "] Area LOCKED: " << area << std::endl;
    triggerEvent("AREA_LOCKED:" + area);
}

void FacilitiesStaff::unlockArea(const std::string& area) {
    std::cout << "    [FacilitiesStaff:" << unitID << "] Area UNLOCKED: " << area << std::endl;
    triggerEvent("AREA_UNLOCKED:" + area);
}

void FacilitiesStaff::restrictAccess(const std::string& area) {
    std::cout << "    [FacilitiesStaff:" << unitID << "] Access RESTRICTED: " << area << std::endl;
    triggerEvent("ACCESS_RESTRICTED:" + area);
}

void FacilitiesStaff::getStatus() {
    std::cout << "    [FacilitiesStaff:" << unitID << "] Status: location="
              << currentLocation << ", available=" << (isAvailable ? "YES" : "NO") << std::endl;
}

void FacilitiesStaff::receiveNotification(const std::string& event) {
    std::cout << "    [FacilitiesStaff:" << unitID << "] << Notification: \""
              << event << "\"" << std::endl;
    // React to broadcast lockdown events from the mediator
    if (event.find("LOCKDOWN:") == 0) {
        std::string area = event.substr(9);
        lockArea(area);
    } else if (event == "EVACUATE_NOW") {
        std::cout << "    [FacilitiesStaff:" << unitID
                  << "] Unlocking emergency exits for evacuation." << std::endl;
    } else if (event == "CHEMICAL_SPILL") {
        restrictAccess("Chemistry Lab Wing");
    }
}
