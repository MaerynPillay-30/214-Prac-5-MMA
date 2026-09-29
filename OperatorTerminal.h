#ifndef OPERATORTERMINAL_H
#define OPERATORTERMINAL_H

#include <vector>

class EmergencyCommand;

/**
 * OperatorTerminal — Command Pattern: Invoker.
 *
 * Executes commands, keeps a history of the ones that succeeded (for undo and
 * the audit trail) and knows nothing about the receivers.
 *
 * Ownership: the terminal takes ownership of every command passed to
 * executeCommand(). A failed command is deleted straight away; a successful one
 * stays in the history until it is undone or the terminal is destroyed.
 */
class OperatorTerminal {
private:
    std::vector<EmergencyCommand*> history; // owned

public:
    OperatorTerminal();
    ~OperatorTerminal();

    void executeCommand(EmergencyCommand* cmd);
    void undoLastCommand();
    void exportAuditTrail() const;

    OperatorTerminal(const OperatorTerminal&) = delete;            // owning: not copyable
    OperatorTerminal& operator=(const OperatorTerminal&) = delete;
};

#endif // OPERATORTERMINAL_H
