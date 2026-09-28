#ifndef SECURITYFACTORY_H
#define SECURITYFACTORY_H

#include "ResponseUnitFactory.h"

/**
 * SecurityFactory — Factory Method Pattern: Concrete Creator.
 * Creates SecurityTeam units.
 */
class SecurityFactory : public ResponseUnitFactory {
public:
    SecurityFactory() {}
    ~SecurityFactory() override {}

protected:
    ResponseComponent* createResponder(CampusCoordinator* coord,
                                       const std::string& unitID,
                                       const std::string& baseLocation) override;
};

#endif // SECURITYFACTORY_H
