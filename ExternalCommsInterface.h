#ifndef EXTERNALCOMMSINTERFACE_H
#define EXTERNALCOMMSINTERFACE_H

#include <string>

/**
 * ExternalCommsInterface — Adapter Pattern: Target interface.
 * This is the interface CampusGuard expects for all external communications.
 * RadioAdapter translates calls on this interface to the LegacyRadioSystem's
 * incompatible API, making the legacy system usable without modification.
 */
class ExternalCommsInterface {
public:
    ExternalCommsInterface() = default;
    virtual ~ExternalCommsInterface() = default;

    virtual void execute() = 0;
    virtual void sendAlert(const std::string& message) = 0;
};

#endif // EXTERNALCOMMSINTERFACE_H
