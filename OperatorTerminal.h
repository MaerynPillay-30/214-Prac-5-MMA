#ifndef OPERATORTERMINAL_H
#define OPERATORTERMINAL_H

#include <vector>
#include "EmergencyCommand.h"

/**
 * OperatorTerminal — Command Pattern: Invoker.
 * Receives command objects from the client (main), executes them, and
 * maintains a history stack that enables undo and audit-trail export.
 * The terminal owns every command it has executed and frees them on destruction.
 */
class OperatorTerminal {
private:
    std::vector<EmergencyCommand*> history;

public:
    OperatorTerminal();
    ~OperatorTerminal();

    void executeCommand(EmergencyCommand* cmd);
    void undoLastCommand();
    void exportAuditTrail();
};

#endif // OPERATORTERMINAL_H
