#include "AlertCommand.h"
#include <iostream>

AlertCommand::AlertCommand(ExternalCommsInterface* recv, const std::string& msg)
    : message(msg), area(""), receiver(recv) {}

void AlertCommand::execute() {
    std::cout << "    [AlertCommand] Broadcasting campus alert via external comms..." << std::endl;
    receiver->sendAlert(message);
}

void AlertCommand::undo() {
    std::cout << "    [AlertCommand] Cancelling alert — broadcasting ALL CLEAR." << std::endl;
    receiver->sendAlert("ALL CLEAR — Previous alert cancelled: " + message);
}

std::string AlertCommand::getCommandName() {
    return "AlertCommand: \"" + message + "\"";
}
