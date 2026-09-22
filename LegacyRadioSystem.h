#ifndef LEGACYRADIOSYSTEM_H
#define LEGACYRADIOSYSTEM_H

#include <string>

/**
 * LegacyRadioSystem — Adapter Pattern: Adaptee.
 * An existing city-radio system with an incompatible interface.
 * CampusGuard cannot use this class directly because it exposes
 * transmitEmergencySignal(int, string) instead of sendAlert(string).
 * RadioAdapter bridges the gap.
 */
class LegacyRadioSystem {
public:
    LegacyRadioSystem() = default;
    ~LegacyRadioSystem() = default;

    void transmitEmergencySignal(int code, const std::string& description);
};

#endif // LEGACYRADIOSYSTEM_H
