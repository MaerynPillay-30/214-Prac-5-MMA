#ifndef RESPONSECOMPONENT_H
#define RESPONSECOMPONENT_H

#include <string>
#include "CampusCoordinator.h"

/**
 * ResponseComponent — Mediator Pattern: Abstract Colleague.
 * Base class for all campus response units (SecurityTeam, MedicalResponder,
 * FacilitiesStaff). Each component holds a reference to the CampusCoordinator
 * (mediator) and communicates events through it rather than directly to peers.
 */
class ResponseComponent {
protected:
    bool isAvailable;
    std::string currentLocation;
    std::string unitID;
    CampusCoordinator* coordinator;

public:
    ResponseComponent(CampusCoordinator* coord, const std::string& id, const std::string& loc);
    virtual ~ResponseComponent() = default;

    virtual void deploy(const std::string& desc, const std::string& loc) = 0;
    virtual void getStatus() = 0;
    virtual void receiveNotification(const std::string& event) = 0;

    void triggerEvent(const std::string& event);
    void setAvailable(bool b);
    std::string getUnitID();
};

#endif // RESPONSECOMPONENT_H
