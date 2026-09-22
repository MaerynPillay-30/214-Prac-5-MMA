#ifndef RESPONSEUNITFACTORY_H
#define RESPONSEUNITFACTORY_H

#include <string>

class ResponseComponent;
class CampusCoordinator;

/**
 * ResponseUnitFactory — Factory Method Pattern: Abstract Creator.
 * Declares the factory method createResponder() that subclasses override
 * to instantiate the correct type of ResponseComponent (Security, Medical,
 * Facilities) without the client needing to know the concrete class.
 */
class ResponseUnitFactory {
public:
    ResponseUnitFactory() = default;
    virtual ~ResponseUnitFactory() = default;

    virtual ResponseComponent* createResponder(CampusCoordinator* coord,
                                               const std::string& unitID,
                                               const std::string& startLocation) = 0;
};

#endif // RESPONSEUNITFACTORY_H
