#ifndef RESOLVEDSTATE_H
#define RESOLVEDSTATE_H

#include "IncidentState.h"

/**
 * ResolvedState — State Pattern: Concrete State.
 * Terminal state. Both escalate() and resolve() are rejected with clear
 * messages — demonstrating sensible handling of invalid operations.
 * Notes are accepted as archived records.
 */
class ResolvedState : public IncidentState {
public:
    explicit ResolvedState(Incident* ctx);
    ~ResolvedState() override = default;

    void escalate(Incident* ctx) override;
    void resolve(Incident* ctx) override;
    void addNotes(Incident* ctx, const std::string& note) override;
};

#endif // RESOLVEDSTATE_H
