#ifndef FACILITIESFACTORY_H
#define FACILITIESFACTORY_H

#include "ResponseUnitFactory.h"

/**
 * FacilitiesFactory — Factory Method Pattern: Concrete Creator.
 * Creates and configures FacilitiesStaff instances, decoupling
 * the caller from construction details.
 */
class FacilitiesFactory : public ResponseUnitFactory {
public:
    FacilitiesFactory() = default;
    ~FacilitiesFactory() override = default;

    ResponseComponent* createResponder(CampusCoordinator* coord,
                                       const std::string& unitID,
                                       const std::string& startLocation) override;
};

#endif // FACILITIESFACTORY_H
