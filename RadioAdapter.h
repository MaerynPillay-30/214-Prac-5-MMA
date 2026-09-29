#ifndef RADIOADAPTER_H
#define RADIOADAPTER_H

#include "ExternalCommsInterface.h"

class LegacyRadioSystem;

/**
 * RadioAdapter — Adapter Pattern: Object Adapter.
 *
 * Implements sendAlert(message) by translating it into the legacy call
 * transmitEmergencySignal(code, description): it works out the numeric
 * signal code the city radio network expects from the alert text.
 *
 * Ownership: the adaptee is NOT owned — the legacy system exists
 * independently of CampusGuard and is created and destroyed by main.
 */
class RadioAdapter : public ExternalCommsInterface {
private:
    LegacyRadioSystem* legacySystem; // not owned

    static int signalCodeFor(const std::string& message);

public:
    explicit RadioAdapter(LegacyRadioSystem* legacy);
    ~RadioAdapter() override {}

    void sendAlert(const std::string& message) override;
};

#endif // RADIOADAPTER_H
