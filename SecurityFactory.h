#ifndef SECURITYFACTORY_H
#define SECURITYFACTORY_H

#include "ResponseUnitFactory.h"

/**
 * SecurityFactory — Factory Method Pattern: Concrete Creator.
 * Creates and configures SecurityTeam instances without the client
 * needing to know construction details or the concrete class name.
 */
class SecurityFactory : public ResponseUnitFactory {
public:
    SecurityFactory() = default;
    ~SecurityFactory() override = default;

    ResponseComponent* createResponder(CampusCoordinator* coord,
                                       const std::string& unitID,
                                       const std::string& startLocation) override;
};

#endif // SECURITYFACTORY_H
