#ifndef CAMPUSCOORDINATOR_H
#define CAMPUSCOORDINATOR_H

#include <string>

class ResponseComponent; // forward declaration

/**
 * CampusCoordinator — Mediator Pattern: abstract Mediator.
 *
 * All traffic between response units goes through the coordinator, so no
 * unit ever holds a pointer to another unit. Two kinds of traffic exist:
 *
 *  - notify():      an event raised BY a response unit (colleague). The
 *                   coordinator relays it to every other unit.
 *  - broadcast(),
 *    dispatchUnit(),
 *    recallUnit():  requests from OUTSIDE the colleague group — operator
 *                   commands, the facade, and incidents changing state.
 */
class CampusCoordinator {
public:
    CampusCoordinator() {}
    virtual ~CampusCoordinator() {}

    virtual void registerComponent(ResponseComponent* component) = 0;
    virtual void notify(ResponseComponent* sender, const std::string& event) = 0;
    virtual void broadcast(const std::string& event) = 0;
    virtual bool dispatchUnit(const std::string& unitID,
                              const std::string& location,
                              const std::string& reason) = 0;
    virtual void recallUnit(const std::string& unitID) = 0;
};

#endif // CAMPUSCOORDINATOR_H
