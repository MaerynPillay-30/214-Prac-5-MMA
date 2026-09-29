#ifndef ACTIVESTATE_H
#define ACTIVESTATE_H

#include "IncidentState.h"

/**
 * ActiveState — State Pattern: Concrete State.
 * Response under way. escalate() raises severity; resolve() moves to RESOLVED.
 */
class ActiveState : public IncidentState {
public:
    ActiveState() {}
    ~ActiveState() override {}

    void escalate(Incident* ctx) override;
    void resolve(Incident* ctx) override;
    void addNote(Incident* ctx, const std::string& note) override;
    std::string getName() const override;
};

#endif // ACTIVESTATE_H
