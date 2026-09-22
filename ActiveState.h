#ifndef ACTIVESTATE_H
#define ACTIVESTATE_H

#include "IncidentState.h"

/**
 * ActiveState — State Pattern: Concrete State.
 * The incident is under active response. escalate() raises severity
 * within the active state. resolve() transitions to ResolvedState.
 */
class ActiveState : public IncidentState {
public:
    explicit ActiveState(Incident* ctx);
    ~ActiveState() override = default;

    void escalate(Incident* ctx) override;
    void resolve(Incident* ctx) override;
    void addNotes(Incident* ctx, const std::string& note) override;
};

#endif // ACTIVESTATE_H
