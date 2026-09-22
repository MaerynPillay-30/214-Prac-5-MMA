#ifndef CAMPUSCOORDINATOR_H
#define CAMPUSCOORDINATOR_H

#include <string>

class ResponseComponent; // forward declaration

/**
 * CampusCoordinator — Mediator Pattern: Abstract Mediator interface.
 * Defines the protocol through which ResponseComponent colleagues
 * communicate without holding direct references to each other.
 */
class CampusCoordinator {
public:
    CampusCoordinator() = default;
    virtual ~CampusCoordinator() = default;

    virtual void notify(ResponseComponent* component, const std::string& event) = 0;
    virtual void registerComponent(ResponseComponent* component) = 0;
};

#endif // CAMPUSCOORDINATOR_H
