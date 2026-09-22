#ifndef REPORTEDSTATE_H
#define REPORTEDSTATE_H

#include "IncidentState.h"

/**
 * ReportedState — State Pattern: Concrete State.
 * Initial state after an incident is logged. The only valid transition
 * from Reported is to Active (escalate). Attempting to resolve a
 * Reported incident is rejected with a clear message.
 */
class ReportedState : public IncidentState {
public:
    explicit ReportedState(Incident* ctx);
    ~ReportedState() override = default;

    void escalate(Incident* ctx) override;
    void resolve(Incident* ctx) override;
    void addNotes(Incident* ctx, const std::string& note) override;
};

#endif // REPORTEDSTATE_H
