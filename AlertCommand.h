#ifndef ALERTCOMMAND_H
#define ALERTCOMMAND_H

#include "EmergencyCommand.h"
#include <string>

class ExternalCommsInterface;

/**
 * AlertCommand — Command Pattern: Concrete Command.
 *
 * "Broadcast this alert off campus." The receiver is the
 * ExternalCommsInterface; at runtime that is a RadioAdapter around the
 * LegacyRadioSystem (Command + Adapter). undo() sends an ALL CLEAR.
 *
 * Ownership: the receiver is NOT owned.
 */
class AlertCommand : public EmergencyCommand {
private:
    ExternalCommsInterface* receiver; // not owned
    std::string message;

public:
    AlertCommand(ExternalCommsInterface* recv, const std::string& msg);
    ~AlertCommand() override {}

    bool execute() override;
    void undo() override;
    std::string getCommandName() const override;
};

#endif // ALERTCOMMAND_H
