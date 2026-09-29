#ifndef FACILITIESSTAFF_H
#define FACILITIESSTAFF_H

#include "ResponseComponent.h"

/**
 * FacilitiesStaff — Mediator Pattern: Concrete Colleague,
 * and Command Pattern: Receiver of LockdownCommand.
 *
 * Owns the building-access capability. Locking or unlocking an area is a
 * change in this colleague that the coordinator relays to the other units
 * (SecurityTeam reacts by securing or leaving the perimeter).
 *
 * Reacts to events relayed by the coordinator:
 *  - INCIDENT_ACTIVE:<loc>     an available crew opens emergency exits there
 *  - INCIDENT_RESOLVED:<loc>   crews at that location stand down
 */
class FacilitiesStaff : public ResponseComponent {
public:
    FacilitiesStaff(CampusCoordinator* coord, const std::string& id, const std::string& base);
    ~FacilitiesStaff() override {}

    void deploy(const std::string& reason, const std::string& location) override;
    void receiveNotification(const std::string& event) override;

    void lockArea(const std::string& area);
    void unlockArea(const std::string& area);
};

#endif // FACILITIESSTAFF_H
