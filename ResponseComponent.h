#ifndef RESPONSECOMPONENT_H
#define RESPONSECOMPONENT_H

#include <string>

class CampusCoordinator;

/**
 * ResponseComponent — Mediator Pattern: abstract Colleague.
 *
 * Base class for every campus response unit (SecurityTeam, MedicalResponder,
 * FacilitiesStaff). A unit only knows its coordinator; it never talks to
 * another unit directly. Each concrete unit decides for itself how to react
 * to an event in receiveNotification(), so the mediator needs no type checks.
 *
 * Ownership: the coordinator pointer is NOT owned (the coordinator owns the unit).
 */
class ResponseComponent {
protected:
    std::string unitID;
    std::string baseLocation;
    std::string currentLocation;
    bool available;
    CampusCoordinator* coordinator; // not owned

    // Raise an event for the coordinator to relay to the other units.
    void triggerEvent(const std::string& event);

    // True if this unit is committed somewhere inside the given area.
    bool isStationedAt(const std::string& area) const;

    // If event starts with prefix, stores the remainder in detail and returns true.
    static bool readEvent(const std::string& event, const std::string& prefix,
                          std::string& detail);

public:
    ResponseComponent(CampusCoordinator* coord, const std::string& id,
                      const std::string& base);
    virtual ~ResponseComponent() {}

    virtual void deploy(const std::string& reason, const std::string& location) = 0;
    virtual void receiveNotification(const std::string& event) = 0;

    void standDown();
    void getStatus() const;
    bool isAvailable() const;
    std::string getUnitID() const;
};

#endif // RESPONSECOMPONENT_H
