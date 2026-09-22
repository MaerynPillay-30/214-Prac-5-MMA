#ifndef DISPATCHCOMMAND_H
#define DISPATCHCOMMAND_H

#include "EmergencyCommand.h"
#include "CampusCoordinator.h"
#include <string>

/**
 * DispatchCommand — Command Pattern: Concrete Command.
 * Encapsulates a "dispatch all available response units to location" action.
 * The receiver is the CampusCoordinator (mediator), which then coordinates
 * which colleagues should respond — demonstrating Command + Mediator interaction.
 * undo() recalls the units by sending a RECALL event through the mediator.
 */
class DispatchCommand : public EmergencyCommand {
private:
    std::string location;
    std::string prevLocation;
    CampusCoordinator* receiver;

public:
    DispatchCommand(CampusCoordinator* recv, const std::string& loc);
    ~DispatchCommand() override = default;

    void execute() override;
    void undo() override;
    std::string getCommandName() override;
};

#endif // DISPATCHCOMMAND_H
