#include "MedicalResponder.h"
#include <iostream>

MedicalResponder::MedicalResponder(CampusCoordinator* coord,
                                   const std::string& id,
                                   const std::string& loc)
    : ResponseComponent(coord, id, loc) {}

void MedicalResponder::deploy(const std::string& desc, const std::string& loc) {
    std::cout << "    [MedicalResponder:" << unitID << "] Deploying to " << loc
              << " — " << desc << std::endl;
    currentLocation = loc;
    isAvailable = false;
    triggerEvent("MEDICAL_DEPLOYED:" + loc);
}

void MedicalResponder::dispatchAmbulance(const std::string& location) {
    std::cout << "    [MedicalResponder:" << unitID << "] Ambulance dispatched to "
              << location << std::endl;
    currentLocation = location;
    isAvailable = false;
}

void MedicalResponder::assessTriage() {
    std::cout << "    [MedicalResponder:" << unitID << "] Triage assessment underway..." << std::endl;
}

void MedicalResponder::provideFirstAid() {
    std::cout << "    [MedicalResponder:" << unitID << "] First aid being administered." << std::endl;
}

void MedicalResponder::requestAirEvac() {
    std::cout << "    [MedicalResponder:" << unitID << "] AIR EVACUATION requested!" << std::endl;
    triggerEvent("AIR_EVAC_REQUESTED");
}

void MedicalResponder::reportCasualties(int count) {
    std::cout << "    [MedicalResponder:" << unitID << "] Casualties reported: "
              << count << std::endl;
}

void MedicalResponder::getStatus() {
    std::cout << "    [MedicalResponder:" << unitID << "] Status: location="
              << currentLocation << ", available=" << (isAvailable ? "YES" : "NO") << std::endl;
}

void MedicalResponder::receiveNotification(const std::string& event) {
    std::cout << "    [MedicalResponder:" << unitID << "] << Notification: \""
              << event << "\"" << std::endl;
    if (event.find("DISPATCH:") == 0) {
        std::string location = event.substr(9);
        dispatchAmbulance(location);
    } else if (event == "CHEMICAL_SPILL") {
        std::cout << "    [MedicalResponder:" << unitID
                  << "] Standing by for HAZMAT casualties." << std::endl;
    } else if (event == "BACKUP_REQUESTED") {
        std::cout << "    [MedicalResponder:" << unitID
                  << "] Moving to support security backup." << std::endl;
    }
}
