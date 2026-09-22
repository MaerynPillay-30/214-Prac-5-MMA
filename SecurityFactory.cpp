#include "SecurityFactory.h"
#include "SecurityTeam.h"
#include <iostream>

ResponseComponent* SecurityFactory::createResponder(CampusCoordinator* coord,
                                                    const std::string& unitID,
                                                    const std::string& startLocation) {
    std::cout << "  [SecurityFactory] Instantiating SecurityTeam: " << unitID
              << " @ " << startLocation << std::endl;
    return new SecurityTeam(coord, unitID, startLocation);
}
