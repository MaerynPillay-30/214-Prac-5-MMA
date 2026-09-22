#include "MedicalFactory.h"
#include "MedicalResponder.h"
#include <iostream>

ResponseComponent* MedicalFactory::createResponder(CampusCoordinator* coord,
                                                   const std::string& unitID,
                                                   const std::string& startLocation) {
    std::cout << "  [MedicalFactory] Instantiating MedicalResponder: " << unitID
              << " @ " << startLocation << std::endl;
    return new MedicalResponder(coord, unitID, startLocation);
}
