#include "ResolvedState.h"
#include "Incident.h"
#include <iostream>

ResolvedState::ResolvedState(Incident* ctx) : IncidentState(ctx) {
    std::cout << "  [Incident:" << ctx->getLocation()
              << "] State  -->  RESOLVED" << std::endl;
}

void ResolvedState::escalate(Incident* ctx) {
    // Invalid operation — sensible failure (requirement 6)
    std::cout << "  [Incident:" << ctx->getLocation()
              << "] ERROR: Cannot escalate a RESOLVED incident." << std::endl;
}

void ResolvedState::resolve(Incident* ctx) {
    // Invalid operation — sensible failure (requirement 6)
    std::cout << "  [Incident:" << ctx->getLocation()
              << "] ERROR: Incident already RESOLVED — no further action needed." << std::endl;
}

void ResolvedState::addNotes(Incident* ctx, const std::string& note) {
    std::cout << "  [Incident:" << ctx->getLocation()
              << "] [RESOLVED] Archived note: " << note << std::endl;
}
