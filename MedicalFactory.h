#ifndef MEDICALFACTORY_H
#define MEDICALFACTORY_H

#include "ResponseUnitFactory.h"

/**
 * MedicalFactory — Factory Method Pattern: Concrete Creator.
 * Creates MedicalResponder units.
 */
class MedicalFactory : public ResponseUnitFactory {
public:
    MedicalFactory() {}
    ~MedicalFactory() override {}

protected:
    ResponseComponent* createResponder(CampusCoordinator* coord,
                                       const std::string& unitID,
                                       const std::string& baseLocation) override;
};

#endif // MEDICALFACTORY_H
