#include "DispatchCommand.h"
#include "CampusCoordinator.h"
#include <iostream>

DispatchCommand::DispatchCommand(CampusCoordinator* recv, const std::string& unit,
                                 const std::string& loc)
    : receiver(recv), unitID(unit), location(loc) {}

bool DispatchCommand::execute() {
    std::cout << "    [DispatchCommand] Requesting " << unitID << " at " << location << std::endl;
    return receiver->dispatchUnit(unitID, location, "operator dispatch");
}

void DispatchCommand::undo() {
    std::cout << "    [DispatchCommand] Cancelling dispatch of " << unitID << std::endl;
    receiver->recallUnit(unitID);
}

std::string DispatchCommand::getCommandName() const {
    return "Dispatch " + unitID + " -> " + location;
}
