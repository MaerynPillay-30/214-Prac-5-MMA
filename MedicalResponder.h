#ifndef MEDICALRESPONDER_H
#define MEDICALRESPONDER_H

#include "ResponseComponent.h"

/**
 * MedicalResponder — Mediator Pattern: Concrete Colleague.
 * Handles medical operations: ambulance dispatch, triage, first aid,
 * air evacuation and casualty reporting. Notifies the coordinator
 * when critical escalation occurs (e.g. air evac needed).
 */
class MedicalResponder : public ResponseComponent {
public:
    MedicalResponder(CampusCoordinator* coord, const std::string& id, const std::string& loc);
    ~MedicalResponder() override = default;

    void deploy(const std::string& desc, const std::string& loc) override;
    void dispatchAmbulance(const std::string& location);
    void assessTriage();
    void provideFirstAid();
    void requestAirEvac();
    void reportCasualties(int count);
    void getStatus() override;
    void receiveNotification(const std::string& event) override;
};

#endif // MEDICALRESPONDER_H
