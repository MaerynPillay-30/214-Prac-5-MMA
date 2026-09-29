#include "FacilitiesFactory.h"
#include "FacilitiesStaff.h"
#include <iostream>

ResponseComponent* FacilitiesFactory::createResponder(CampusCoordinator* coord,
                                                 const std::string& unitID,
                                                 const std::string& baseLocation) {
    std::cout << "  [FacilitiesFactory] Creating FacilitiesStaff " << unitID
              << " based at " << baseLocation << std::endl;
    return new FacilitiesStaff(coord, unitID, baseLocation);
}
