#ifndef INCIDENT_H
#define INCIDENT_H

#include <string>

class IncidentState;

/**
 * Incident — State Pattern: Context.
 * Represents an emergency event on campus. All behaviour that depends
 * on operational status (escalate, resolve, addNotes) is delegated to
 * the current IncidentState object, making invalid transitions impossible
 * and keeping the Incident class free of conditional branching.
 *
 * Ownership: Incident owns its current IncidentState* exclusively.
 */
class Incident {
private:
    std::string description;
    std::string location;
    int severityLevel;
    int casualtyCount;
    std::string timestamp;
    IncidentState* state;

public:
    Incident(const std::string& desc, const std::string& loc,
             int sev, const std::string& time);
    ~Incident();

    // Called by concrete states to perform a safe state transition
    void changeState(IncidentState* newState);

    void escalate();
    void resolve();
    void addNotes(const std::string& note);

    std::string getDescription() const;
    std::string getLocation() const;
    int getSeverityLevel() const;
};

#endif // INCIDENT_H
