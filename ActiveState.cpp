#include "ActiveState.h"
#include "ResolvedState.h"
#include "Incident.h"
#include <iostream>

void ActiveState::escalate(Incident* ctx) {
    ctx->raiseSeverity();
    std::cout << "  [Incident:" << ctx->getLocation()
              << "] Already ACTIVE — severity raised to " << ctx->getSeverityLevel()
              << "/10" << std::endl;
}

void ActiveState::resolve(Incident* ctx) {
    std::cout << "  [Incident:" << ctx->getLocation()
              << "] Incident contained — resolving" << std::endl;
    ctx->changeState(new ResolvedState()); // deletes this object: return immediately
}

void ActiveState::addNote(Incident* ctx, const std::string& note) {
    std::cout << "  [Incident:" << ctx->getLocation() << "] [ACTIVE] Note: "
              << note << std::endl;
}

std::string ActiveState::getName() const {
    return "ACTIVE";
}
