#ifndef REPORTEDSTATE_H
#define REPORTEDSTATE_H

#include "IncidentState.h"

/**
 * ReportedState — State Pattern: Concrete State.
 * Initial state. escalate() moves to ACTIVE; resolve() is rejected.
 */
class ReportedState : public IncidentState {
public:
    ReportedState() {}
    ~ReportedState() override {}

    void escalate(Incident* ctx) override;
    void resolve(Incident* ctx) override;
    void addNote(Incident* ctx, const std::string& note) override;
    std::string getName() const override;
};

#endif // REPORTEDSTATE_H
