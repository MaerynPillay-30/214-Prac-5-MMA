#ifndef SECURITYTEAM_H
#define SECURITYTEAM_H

#include "ResponseComponent.h"

/**
 * SecurityTeam — Mediator Pattern: Concrete Colleague.
 * Handles security operations: team dispatch, area patrol, suspect detention
 * and escalation. Communicates all significant state changes back through
 * the CampusCoordinator so other colleagues can react.
 */
class SecurityTeam : public ResponseComponent {
public:
    SecurityTeam(CampusCoordinator* coord, const std::string& id, const std::string& loc);
    ~SecurityTeam() override = default;

    void deploy(const std::string& desc, const std::string& loc) override;
    void dispatchTeam(const std::string& location);
    void requestBackup();
    void reportStatus();
    void detainSuspect();
    void escalateLevel();
    void getStatus() override;
    void receiveNotification(const std::string& event) override;
};

#endif // SECURITYTEAM_H
