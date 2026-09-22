#include "ReportedState.h"
#include "ActiveState.h"
#include "Incident.h"
#include <iostream>

ReportedState::ReportedState(Incident* ctx) : IncidentState(ctx) {
    std::cout << "  [Incident:" << ctx->getLocation()
              << "] State  -->  REPORTED" << std::endl;
}

void ReportedState::escalate(Incident* ctx) {
    std::cout << "  [Incident:" << ctx->getLocation()
              << "] REPORTED --> escalating to ACTIVE" << std::endl;
    // IMPORTANT: changeState deletes 'this'. Do not access members after this call.
    ctx->changeState(new ActiveState(ctx));
}

void ReportedState::resolve(Incident* ctx) {
    // Invalid transition — sensible failure handling (requirement 6)
    std::cout << "  [Incident:" << ctx->getLocation()
              << "] ERROR: Cannot resolve a REPORTED incident. Escalate first." << std::endl;
}

void ReportedState::addNotes(Incident* ctx, const std::string& note) {
    std::cout << "  [Incident:" << ctx->getLocation()
              << "] [REPORTED] Note: " << note << std::endl;
}
