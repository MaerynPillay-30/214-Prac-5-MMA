#include "LegacyRadioSystem.h"
#include <iostream>

void LegacyRadioSystem::transmitEmergencySignal(int code, const std::string& description) {
    std::cout << "  [LegacyRadio] >> Transmitting signal [CODE " << code << "]: \""
              << description << "\"" << std::endl;
}
