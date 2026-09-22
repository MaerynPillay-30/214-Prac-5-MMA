#include "Incident.h"
#include "IncidentState.h"
#include <iostream>

Incident::Incident(const std::string& desc, const std::string& loc,
                   int sev, const std::string& time)
    : description(desc), location(loc), severityLevel(sev),
      casualtyCount(0), timestamp(time), state(nullptr) {
    std::cout << "  [Incident] Created: \"" << description << "\" at " << location
              << " (severity=" << severityLevel << ", time=" << timestamp << ")" << std::endl;
}

Incident::~Incident() {
    delete state;
    state = nullptr;
}

void Incident::changeState(IncidentState* newState) {
    delete state;     // safe — deleting nullptr is a no-op in C++
    state = newState;
}

void Incident::escalate() {
    if (state) {
        state->escalate(this);
    } else {
        std::cout << "  [Incident:" << location << "] No state set — cannot escalate." << std::endl;
    }
}

void Incident::resolve() {
    if (state) {
        state->resolve(this);
    } else {
        std::cout << "  [Incident:" << location << "] No state set — cannot resolve." << std::endl;
    }
}

void Incident::addNotes(const std::string& note) {
    if (state) {
        state->addNotes(this, note);
    } else {
        std::cout << "  [Incident:" << location << "] No state set — cannot add notes." << std::endl;
    }
}

std::string Incident::getDescription() const { return description; }
std::string Incident::getLocation()    const { return location; }
int         Incident::getSeverityLevel() const { return severityLevel; }
