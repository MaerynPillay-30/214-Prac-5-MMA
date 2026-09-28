#include "RadioAdapter.h"
#include "LegacyRadioSystem.h"
#include <iostream>

RadioAdapter::RadioAdapter(LegacyRadioSystem* legacy) : legacySystem(legacy) {}

// Legacy city-radio signal codes, looked up in priority order.
int RadioAdapter::signalCodeFor(const std::string& message) {
    struct CodeRule { const char* keyword; int code; };
    static const CodeRule rules[] = {
        { "ALL CLEAR", 0   },
        { "HAZMAT",    202 },
        { "FIRE",      101 },
        { "LOCKDOWN",  404 },
        { "EVACUAT",   505 },
    };
    for (std::size_t i = 0; i < sizeof(rules) / sizeof(rules[0]); ++i) {
        if (message.find(rules[i].keyword) != std::string::npos) {
            return rules[i].code;
        }
    }
    return 911; // general emergency
}

void RadioAdapter::sendAlert(const std::string& message) {
    int code = signalCodeFor(message);
    std::cout << "  [RadioAdapter] sendAlert() -> transmitEmergencySignal(" << code
              << ", ...)" << std::endl;
    legacySystem->transmitEmergencySignal(code, message);
}
