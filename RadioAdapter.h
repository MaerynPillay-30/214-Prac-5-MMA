#ifndef RADIOADAPTER_H
#define RADIOADAPTER_H

#include "ExternalCommsInterface.h"
#include "LegacyRadioSystem.h"

/**
 * RadioAdapter — Adapter Pattern: Object Adapter.
 * Implements the ExternalCommsInterface (target) expected by CampusGuard
 * and internally delegates to LegacyRadioSystem (adaptee), translating
 * the modern sendAlert(string) call into the legacy transmitEmergencySignal(int, string).
 * The adapter is necessary because simply wrapping the class without changing
 * the interface would not allow polymorphic substitution.
 */
class RadioAdapter : public ExternalCommsInterface {
private:
    LegacyRadioSystem* legacySystem;

public:
    explicit RadioAdapter(LegacyRadioSystem* legacy);
    ~RadioAdapter() = default;

    void execute() override;
    void sendAlert(const std::string& message) override;
};

#endif // RADIOADAPTER_H
