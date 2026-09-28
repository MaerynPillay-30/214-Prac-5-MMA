#include "ResolvedState.h"
#include "Incident.h"
#include <iostream>

void ResolvedState::escalate(Incident* ctx) {
    std::cout << "  [Incident:" << ctx->getLocation()
              << "] ERROR: Cannot escalate a RESOLVED incident — report a new incident instead."
              << std::endl;
}

void ResolvedState::resolve(Incident* ctx) {
    std::cout << "  [Incident:" << ctx->getLocation()
              << "] ERROR: Incident is already RESOLVED." << std::endl;
}

void ResolvedState::addNote(Incident* ctx, const std::string& note) {
    std::cout << "  [Incident:" << ctx->getLocation() << "] [RESOLVED] Archived note: "
              << note << std::endl;
}

std::string ResolvedState::getName() const {
    return "RESOLVED";
}
