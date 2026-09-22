#ifndef MEDICALFACTORY_H
#define MEDICALFACTORY_H

#include "ResponseUnitFactory.h"

/**
 * MedicalFactory — Factory Method Pattern: Concrete Creator.
 * Creates and configures MedicalResponder instances, decoupling
 * the caller from construction details.
 */
class MedicalFactory : public ResponseUnitFactory {
public:
    MedicalFactory() = default;
    ~MedicalFactory() override = default;

    ResponseComponent* createResponder(CampusCoordinator* coord,
                                       const std::string& unitID,
                                       const std::string& startLocation) override;
};

#endif // MEDICALFACTORY_H
