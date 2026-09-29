#ifndef RESPONSEUNITFACTORY_H
#define RESPONSEUNITFACTORY_H

#include <string>

class ResponseComponent;
class CampusCoordinator;

/**
 * ResponseUnitFactory — Factory Method Pattern: abstract Creator.
 *
 * commissionUnit() is the creator's operation: it brings a new unit onto the
 * response network (create it, then register it with the coordinator). The
 * one step that varies — WHICH kind of unit gets created — is deferred to the
 * factory method createResponder(), overridden by each concrete factory.
 *
 * Ownership: the new unit is handed to the coordinator, which owns it.
 */
class ResponseUnitFactory {
public:
    ResponseUnitFactory() {}
    virtual ~ResponseUnitFactory() {}

    ResponseComponent* commissionUnit(CampusCoordinator* coord,
                                      const std::string& unitID,
                                      const std::string& baseLocation);

protected:
    // The factory method.
    virtual ResponseComponent* createResponder(CampusCoordinator* coord,
                                               const std::string& unitID,
                                               const std::string& baseLocation) = 0;
};

#endif // RESPONSEUNITFACTORY_H
