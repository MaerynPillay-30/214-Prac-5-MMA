#include "MedicalFactory.h"
#include "MedicalResponder.h"
#include <iostream>

ResponseComponent* MedicalFactory::createResponder(CampusCoordinator* coord,
                                                 const std::string& unitID,
                                                 const std::string& baseLocation) {
    std::cout << "  [MedicalFactory] Creating MedicalResponder " << unitID
              << " based at " << baseLocation << std::endl;
    return new MedicalResponder(coord, unitID, baseLocation);
}
