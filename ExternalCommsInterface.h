#ifndef EXTERNALCOMMSINTERFACE_H
#define EXTERNALCOMMSINTERFACE_H

#include <string>

/**
 * ExternalCommsInterface — Adapter Pattern: Target.
 *
 * The interface CampusGuard wants for off-campus communication: send one
 * plain-text alert. RadioAdapter makes the LegacyRadioSystem fit it.
 */
class ExternalCommsInterface {
public:
    ExternalCommsInterface() {}
    virtual ~ExternalCommsInterface() {}

    virtual void sendAlert(const std::string& message) = 0;
};

#endif // EXTERNALCOMMSINTERFACE_H
