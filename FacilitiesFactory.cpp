#include "FacilitiesFactory.h"
#include "FacilitiesStaff.h"
#include <iostream>

ResponseComponent* FacilitiesFactory::createResponder(CampusCoordinator* coord,
                                                      const std::string& unitID,
                                                      const std::string& startLocation) {
    std::cout << "  [FacilitiesFactory] Instantiating FacilitiesStaff: " << unitID
              << " @ " << startLocation << std::endl;
    return new FacilitiesStaff(coord, unitID, startLocation);
}
