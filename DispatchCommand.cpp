#include "DispatchCommand.h"
#include <iostream>

DispatchCommand::DispatchCommand(CampusCoordinator* recv, const std::string& loc)
    : location(loc), prevLocation(""), receiver(recv) {}

void DispatchCommand::execute() {
    std::cout << "    [DispatchCommand] Sending DISPATCH event to mediator for: "
              << location << std::endl;
    // Command triggers mediator to coordinate which colleagues should respond.
    // nullptr sender = command-initiated (not from a specific colleague).
    receiver->notify(nullptr, "DISPATCH:" + location);
}

void DispatchCommand::undo() {
    std::cout << "    [DispatchCommand] Sending RECALL event to mediator for: "
              << location << std::endl;
    receiver->notify(nullptr, "RECALL:" + location);
}

std::string DispatchCommand::getCommandName() {
    return "DispatchCommand -> " + location;
}
