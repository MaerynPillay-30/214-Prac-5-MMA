#ifndef EMERGENCYMEDIATOR_H
#define EMERGENCYMEDIATOR_H

#include "CampusCoordinator.h"
#include <vector>
#include <string>

class ResponseComponent;

/**
 * EmergencyMediator — Mediator Pattern: Concrete Mediator.
 * Maintains the list of registered ResponseComponent colleagues.
 * When one colleague fires an event, the mediator decides which other
 * colleagues must react, keeping all inter-component coupling inside
 * this single class rather than scattered across the campus units.
 */
class EmergencyMediator : public CampusCoordinator {
private:
    std::vector<ResponseComponent*> components;

public:
    EmergencyMediator();
    ~EmergencyMediator() = default;

    void notify(ResponseComponent* sender, const std::string& event) override;
    void registerComponent(ResponseComponent* component) override;
    void broadcastToAll(const std::string& event);
    std::string getComponentStatus(const std::string& unitID);
};

#endif // EMERGENCYMEDIATOR_H
