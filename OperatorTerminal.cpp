#include "OperatorTerminal.h"
#include <iostream>

OperatorTerminal::OperatorTerminal() {}

OperatorTerminal::~OperatorTerminal() {
    // Owns all commands remaining in history — clean up on destruction
    for (auto* cmd : history) {
        delete cmd;
    }
    history.clear();
}

void OperatorTerminal::executeCommand(EmergencyCommand* cmd) {
    std::cout << "  [OperatorTerminal] Executing command: \"" << cmd->getCommandName()
              << "\"" << std::endl;
    cmd->execute();
    history.push_back(cmd);
}

void OperatorTerminal::undoLastCommand() {
    if (history.empty()) {
        // Sensible invalid-operation handling (requirement 6)
        std::cout << "  [OperatorTerminal] ERROR: No commands in history to undo." << std::endl;
        return;
    }
    EmergencyCommand* cmd = history.back();
    history.pop_back();
    std::cout << "  [OperatorTerminal] Undoing: \"" << cmd->getCommandName() << "\"" << std::endl;
    cmd->undo();
    delete cmd; // ownership transferred: we executed and now undo-destroyed it
}

void OperatorTerminal::exportAuditTrail() {
    std::cout << "\n  [OperatorTerminal] ========= AUDIT TRAIL =========" << std::endl;
    if (history.empty()) {
        std::cout << "  [OperatorTerminal]   (history is empty)" << std::endl;
    } else {
        for (std::size_t i = 0; i < history.size(); ++i) {
            std::cout << "  [OperatorTerminal]   " << (i + 1) << ". "
                      << history[i]->getCommandName() << std::endl;
        }
    }
    std::cout << "  [OperatorTerminal] ======= END OF TRAIL =========\n" << std::endl;
}
