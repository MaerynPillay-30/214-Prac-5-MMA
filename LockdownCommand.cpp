#include "LockdownCommand.h"
#include "FacilitiesStaff.h"
#include <iostream>

LockdownCommand::LockdownCommand(FacilitiesStaff* recv, const std::string& s)
    : receiver(recv), area(s) {}

void LockdownCommand::execute() {
    std::cout << "    [LockdownCommand] Initiating lockdown for area: " << area << std::endl;
    receiver->lockArea(area);
}

void LockdownCommand::undo() {
    std::cout << "    [LockdownCommand] Lifting lockdown for area: " << area << std::endl;
    receiver->unlockArea(area);
}

std::string LockdownCommand::getCommandName() {
    return "LockdownCommand: \"" + area + "\"";
}
