#include "RadioAdapter.h"
#include <iostream>

RadioAdapter::RadioAdapter(LegacyRadioSystem* legacy) : legacySystem(legacy) {}

void RadioAdapter::execute() {
    std::cout << "  [RadioAdapter] Legacy radio system initialised and online." << std::endl;
}

void RadioAdapter::sendAlert(const std::string& message) {
    std::cout << "  [RadioAdapter] Translating modern alert to legacy signal format..." << std::endl;
    // Determine signal code based on message content (simplified mapping)
    int code = 911;
    if (message.find("FIRE") != std::string::npos) {
        code = 101;
    } else if (message.find("CHEMICAL") != std::string::npos || message.find("HAZMAT") != std::string::npos) {
        code = 202;
    } else if (message.find("MEDICAL") != std::string::npos) {
        code = 303;
    } else if (message.find("LOCKDOWN") != std::string::npos) {
        code = 404;
    } else if (message.find("EVACUAT") != std::string::npos) {
        code = 505;
    } else if (message.find("ALL CLEAR") != std::string::npos || message.find("cancelled") != std::string::npos) {
        code = 000;
    }
    legacySystem->transmitEmergencySignal(code, message);
}
