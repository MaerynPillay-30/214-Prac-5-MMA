#include "ReportedState.h"
#include "ActiveState.h"
#include "Incident.h"
#include <iostream>

void ReportedState::escalate(Incident* ctx) {
    std::cout << "  [Incident:" << ctx->getLocation()
              << "] Response confirmed — activating incident" << std::endl;
    ctx->changeState(new ActiveState()); // deletes this object: return immediately
}

void ReportedState::resolve(Incident* ctx) {
    std::cout << "  [Incident:" << ctx->getLocation()
              << "] ERROR: Cannot resolve a REPORTED incident — it must be activated first."
              << std::endl;
}

void ReportedState::addNote(Incident* ctx, const std::string& note) {
    std::cout << "  [Incident:" << ctx->getLocation() << "] [REPORTED] Note: "
              << note << std::endl;
}

std::string ReportedState::getName() const {
    return "REPORTED";
}
