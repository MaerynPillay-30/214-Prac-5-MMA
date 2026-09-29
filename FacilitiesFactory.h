#ifndef FACILITIESFACTORY_H
#define FACILITIESFACTORY_H

#include "ResponseUnitFactory.h"

/**
 * FacilitiesFactory — Factory Method Pattern: Concrete Creator.
 * Creates FacilitiesStaff units.
 */
class FacilitiesFactory : public ResponseUnitFactory {
public:
    FacilitiesFactory() {}
    ~FacilitiesFactory() override {}

protected:
    ResponseComponent* createResponder(CampusCoordinator* coord,
                                       const std::string& unitID,
                                       const std::string& baseLocation) override;
};

#endif // FACILITIESFACTORY_H
