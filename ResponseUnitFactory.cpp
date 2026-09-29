#include "ResponseUnitFactory.h"
#include "ResponseComponent.h"
#include "CampusCoordinator.h"

ResponseComponent* ResponseUnitFactory::commissionUnit(CampusCoordinator* coord,
                                                       const std::string& unitID,
                                                       const std::string& baseLocation) {
    ResponseComponent* unit = createResponder(coord, unitID, baseLocation); // factory method
    coord->registerComponent(unit); // coordinator takes ownership
    return unit;
}
