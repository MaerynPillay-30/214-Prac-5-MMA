#ifndef INCIDENTSTATE_H
#define INCIDENTSTATE_H

#include <string>

class Incident; // forward declaration

/**
 * IncidentState — State Pattern: abstract State.
 *
 * Each concrete state decides which operations are valid and which state
 * comes next: Reported -> Active -> Resolved. Invalid requests are rejected
 * with a clear message instead of being silently ignored.
 */
class IncidentState {
public:
    IncidentState() {}
    virtual ~IncidentState() {}

    virtual void escalate(Incident* ctx) = 0;
    virtual void resolve(Incident* ctx) = 0;
    virtual void addNote(Incident* ctx, const std::string& note) = 0;
    virtual std::string getName() const = 0;
};

#endif // INCIDENTSTATE_H
