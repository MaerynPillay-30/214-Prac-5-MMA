#include "AlertCommand.h"
#include "ExternalCommsInterface.h"
#include <iostream>

AlertCommand::AlertCommand(ExternalCommsInterface* recv, const std::string& msg)
    : receiver(recv), message(msg) {}

bool AlertCommand::execute() {
    std::cout << "    [AlertCommand] Sending alert via external comms" << std::endl;
    receiver->sendAlert(message);
    return true;
}

void AlertCommand::undo() {
    std::cout << "    [AlertCommand] Retracting alert" << std::endl;
    receiver->sendAlert("ALL CLEAR — retracted: " + message);
}

std::string AlertCommand::getCommandName() const {
    return "Alert \"" + message + "\"";
}
