#include "LockdownCommand.h"
#include "FacilitiesStaff.h"
#include <iostream>

LockdownCommand::LockdownCommand(FacilitiesStaff* recv, const std::string& a)
    : receiver(recv), area(a) {}

bool LockdownCommand::execute() {
    std::cout << "    [LockdownCommand] Locking down " << area << std::endl;
    receiver->lockArea(area);
    return true;
}

void LockdownCommand::undo() {
    std::cout << "    [LockdownCommand] Lifting lockdown of " << area << std::endl;
    receiver->unlockArea(area);
}

std::string LockdownCommand::getCommandName() const {
    return "Lockdown " + area;
}
