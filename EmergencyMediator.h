#ifndef EMERGENCYMEDIATOR_H
#define EMERGENCYMEDIATOR_H

#include "CampusCoordinator.h"
#include <string>
#include <vector>

/**
 * EmergencyMediator — Mediator Pattern: Concrete Mediator.
 *
 * Keeps the registry of response units and routes every event between them.
 *
 * Ownership: the mediator OWNS every registered ResponseComponent and deletes
 * them in its destructor. Units are handed over by ResponseUnitFactory::
 * commissionUnit(). Copying is disabled so ownership can never be duplicated.
 */
class EmergencyMediator : public CampusCoordinator {
private:
    std::vector<ResponseComponent*> components; // owned

    ResponseComponent* findUnit(const std::string& unitID) const;

public:
    EmergencyMediator();
    ~EmergencyMediator() override;

    void registerComponent(ResponseComponent* component) override;
    void notify(ResponseComponent* sender, const std::string& event) override;
    void broadcast(const std::string& event) override;
    bool dispatchUnit(const std::string& unitID,
                      const std::string& location,
                      const std::string& reason) override;
    void recallUnit(const std::string& unitID) override;

    void printRoster() const;

    EmergencyMediator(const EmergencyMediator&) = delete;            // owning: not copyable
    EmergencyMediator& operator=(const EmergencyMediator&) = delete;
};

#endif // EMERGENCYMEDIATOR_H
