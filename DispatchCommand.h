#ifndef DISPATCHCOMMAND_H
#define DISPATCHCOMMAND_H

#include "EmergencyCommand.h"
#include <string>

class CampusCoordinator;

/**
 * DispatchCommand — Command Pattern: Concrete Command.
 *
 * "Send unit X to location Y." The receiver is the CampusCoordinator
 * (Mediator), which finds the unit and checks it is available before
 * deploying it. undo() recalls the unit to its base.
 *
 * Ownership: the receiver is NOT owned.
 */
class DispatchCommand : public EmergencyCommand {
private:
    CampusCoordinator* receiver; // not owned
    std::string unitID;
    std::string location;

public:
    DispatchCommand(CampusCoordinator* recv, const std::string& unit,
                    const std::string& loc);
    ~DispatchCommand() override {}

    bool execute() override;
    void undo() override;
    std::string getCommandName() const override;
};

#endif // DISPATCHCOMMAND_H
