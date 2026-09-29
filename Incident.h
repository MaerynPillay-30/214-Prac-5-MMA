#ifndef INCIDENT_H
#define INCIDENT_H

#include <string>

class IncidentState;
class CampusCoordinator;

/**
 * Incident — State Pattern: Context.
 *
 * An emergency on campus. escalate(), resolve() and addNote() behave
 * differently depending on the current IncidentState, so Incident itself has
 * no status switch. Every new incident starts in the Reported state.
 *
 * Each state change is announced to the CampusCoordinator (Mediator), which
 * is how response units coordinate when an incident's condition changes.
 *
 * Ownership: Incident OWNS its current IncidentState and deletes it on every
 * transition and in its destructor. The coordinator pointer is NOT owned.
 */
class Incident {
private:
    std::string description;
    std::string location;
    int severityLevel;
    std::string timestamp;
    IncidentState* state;            // owned
    CampusCoordinator* coordinator;  // not owned

public:
    Incident(CampusCoordinator* coord, const std::string& desc,
             const std::string& loc, int severity, const std::string& time);
    ~Incident();

    // Called by concrete states. Deletes the old state, so a state must not
    // touch its own members after calling this.
    void changeState(IncidentState* newState);

    void escalate();
    void resolve();
    void addNote(const std::string& note);

    void raiseSeverity();
    std::string getLocation() const;
    int getSeverityLevel() const;

    Incident(const Incident&) = delete;             // owning: not copyable
    Incident& operator=(const Incident&) = delete;
};

#endif // INCIDENT_H
