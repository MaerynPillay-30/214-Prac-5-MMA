#include "ActiveState.h"
#include "ResolvedState.h"
#include "Incident.h"
#include <iostream>

ActiveState::ActiveState(Incident* ctx) : IncidentState(ctx) {
    std::cout << "  [Incident:" << ctx->getLocation()
              << "] State  -->  ACTIVE" << std::endl;
}

void ActiveState::escalate(Incident* ctx) {
    // Incident already active — raise severity in place (no state change)
    std::cout << "  [Incident:" << ctx->getLocation()
              << "] WARNING: Incident already ACTIVE — raising response severity (level "
              << ctx->getSeverityLevel() << ")." << std::endl;
}

void ActiveState::resolve(Incident* ctx) {
    std::cout << "  [Incident:" << ctx->getLocation()
              << "] ACTIVE --> resolving -> RESOLVED" << std::endl;
    ctx->changeState(new ResolvedState(ctx));
}

void ActiveState::addNotes(Incident* ctx, const std::string& note) {
    std::cout << "  [Incident:" << ctx->getLocation()
              << "] [ACTIVE] Note: " << note << std::endl;
}
