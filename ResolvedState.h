#ifndef RESOLVEDSTATE_H
#define RESOLVEDSTATE_H

#include "IncidentState.h"

/**
 * ResolvedState — State Pattern: Concrete State.
 * Final state. escalate() and resolve() are rejected; notes are archived.
 */
class ResolvedState : public IncidentState {
public:
    ResolvedState() {}
    ~ResolvedState() override {}

    void escalate(Incident* ctx) override;
    void resolve(Incident* ctx) override;
    void addNote(Incident* ctx, const std::string& note) override;
    std::string getName() const override;
};

#endif // RESOLVEDSTATE_H
