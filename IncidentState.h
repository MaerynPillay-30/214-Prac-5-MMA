#ifndef INCIDENTSTATE_H
#define INCIDENTSTATE_H

#include <string>

class Incident; // forward declaration

/**
 * IncidentState — State Pattern: Abstract State interface.
 * Controls the lifecycle of an Incident. Concrete states (Reported, Active,
 * Resolved) define which transitions are valid and what happens during each,
 * preventing invalid state jumps and removing large switch statements from Incident.
 */
class IncidentState {
protected:
    Incident* context;

public:
    explicit IncidentState(Incident* ctx);
    virtual ~IncidentState() = default;

    virtual void escalate(Incident* ctx) = 0;
    virtual void resolve(Incident* ctx) = 0;
    virtual void addNotes(Incident* ctx, const std::string& note) = 0;
};

#endif // INCIDENTSTATE_H
