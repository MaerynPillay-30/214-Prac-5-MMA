#ifndef SECURITYTEAM_H
#define SECURITYTEAM_H

#include "ResponseComponent.h"

/**
 * SecurityTeam — Mediator Pattern: Concrete Colleague.
 *
 * Reacts to events relayed by the coordinator:
 *  - AREA_LOCKED:<area>        an available team secures the perimeter
 *  - AREA_UNLOCKED:<area>      teams guarding that area stand down
 *  - INCIDENT_RESOLVED:<loc>   teams at that location stand down
 */
class SecurityTeam : public ResponseComponent {
public:
    SecurityTeam(CampusCoordinator* coord, const std::string& id, const std::string& base);
    ~SecurityTeam() override {}

    void deploy(const std::string& reason, const std::string& location) override;
    void receiveNotification(const std::string& event) override;
};

#endif // SECURITYTEAM_H
