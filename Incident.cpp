#include "Incident.h"
#include "IncidentState.h"
#include "ReportedState.h"
#include "CampusCoordinator.h"
#include <iostream>

Incident::Incident(CampusCoordinator* coord, const std::string& desc,
                   const std::string& loc, int severity, const std::string& time)
    : description(desc), location(loc), severityLevel(severity),
      timestamp(time), state(new ReportedState()), coordinator(coord) {
    std::cout << "  [Incident] Registered at " << timestamp << ": \"" << description
              << "\" at " << location << " (severity " << severityLevel << "/10, status "
              << state->getName() << ")" << std::endl;
}

Incident::~Incident() {
    delete state;
}

void Incident::changeState(IncidentState* newState) {
    IncidentState* oldState = state;
    state = newState;
    std::cout << "  [Incident:" << location << "] Status " << oldState->getName()
              << " --> " << state->getName() << std::endl;
    delete oldState;

    // Tell the response network that this incident's condition changed.
    if (coordinator != nullptr) {
        coordinator->broadcast("INCIDENT_" + state->getName() + ":" + location);
    }
}

void Incident::escalate() {
    state->escalate(this);
}

void Incident::resolve() {
    state->resolve(this);
}

void Incident::addNote(const std::string& note) {
    state->addNote(this, note);
}

void Incident::raiseSeverity() {
    if (severityLevel < 10) {
        ++severityLevel;
    }
}

std::string Incident::getLocation() const {
    return location;
}

int Incident::getSeverityLevel() const {
    return severityLevel;
}
