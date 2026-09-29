#include "SecurityFactory.h"
#include "SecurityTeam.h"
#include <iostream>

ResponseComponent* SecurityFactory::createResponder(CampusCoordinator* coord,
                                                 const std::string& unitID,
                                                 const std::string& baseLocation) {
    std::cout << "  [SecurityFactory] Creating SecurityTeam " << unitID
              << " based at " << baseLocation << std::endl;
    return new SecurityTeam(coord, unitID, baseLocation);
}
