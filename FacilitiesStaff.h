#ifndef FACILITIESSTAFF_H
#define FACILITIESSTAFF_H

#include "ResponseComponent.h"

/**
 * FacilitiesStaff — Mediator Pattern: Concrete Colleague.
 * Handles physical access control: locking areas, unlocking doors and
 * restricting zones. Acts as the receiver for LockdownCommand and
 * responds to LOCKDOWN events broadcast by the mediator.
 */
class FacilitiesStaff : public ResponseComponent {
public:
    FacilitiesStaff(CampusCoordinator* coord, const std::string& id, const std::string& loc);
    ~FacilitiesStaff() override = default;

    void deploy(const std::string& desc, const std::string& loc) override;
    void lockArea(const std::string& area);
    void unlockArea(const std::string& area);
    void restrictAccess(const std::string& area);
    void getStatus() override;
    void receiveNotification(const std::string& event) override;
};

#endif // FACILITIESSTAFF_H
