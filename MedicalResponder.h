#ifndef MEDICALRESPONDER_H
#define MEDICALRESPONDER_H

#include "ResponseComponent.h"

/**
 * MedicalResponder — Mediator Pattern: Concrete Colleague.
 *
 * Reacts to events relayed by the coordinator:
 *  - HAZMAT:<loc>              an available crew goes to triage casualties
 *  - INCIDENT_RESOLVED:<loc>   crews at that location stand down
 */
class MedicalResponder : public ResponseComponent {
public:
    MedicalResponder(CampusCoordinator* coord, const std::string& id, const std::string& base);
    ~MedicalResponder() override {}

    void deploy(const std::string& reason, const std::string& location) override;
    void receiveNotification(const std::string& event) override;
};

#endif // MEDICALRESPONDER_H
