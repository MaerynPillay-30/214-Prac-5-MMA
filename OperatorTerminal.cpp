#include "OperatorTerminal.h"
#include "EmergencyCommand.h"
#include <iostream>

OperatorTerminal::OperatorTerminal() {}

OperatorTerminal::~OperatorTerminal() {
    for (std::size_t i = 0; i < history.size(); ++i) {
        delete history[i];
    }
    history.clear();
}

void OperatorTerminal::executeCommand(EmergencyCommand* cmd) {
    if (cmd == nullptr) {
        return;
    }
    std::cout << "  [OperatorTerminal] Executing: " << cmd->getCommandName() << std::endl;
    if (cmd->execute()) {
        history.push_back(cmd);
    } else {
        std::cout << "  [OperatorTerminal] Command failed — not recorded in history." << std::endl;
        delete cmd;
    }
}

void OperatorTerminal::undoLastCommand() {
    if (history.empty()) {
        std::cout << "  [OperatorTerminal] ERROR: Nothing to undo — history is empty." << std::endl;
        return;
    }
    EmergencyCommand* cmd = history.back();
    history.pop_back();
    std::cout << "  [OperatorTerminal] Undoing: " << cmd->getCommandName() << std::endl;
    cmd->undo();
    delete cmd;
}

void OperatorTerminal::exportAuditTrail() const {
    std::cout << "\n  [OperatorTerminal] ========== AUDIT TRAIL ==========" << std::endl;
    if (history.empty()) {
        std::cout << "  [OperatorTerminal]   (no commands in history)" << std::endl;
    }
    for (std::size_t i = 0; i < history.size(); ++i) {
        std::cout << "  [OperatorTerminal]   " << (i + 1) << ". "
                  << history[i]->getCommandName() << std::endl;
    }
    std::cout << "  [OperatorTerminal] =================================\n" << std::endl;
}
