#ifndef ALERTCOMMAND_H
#define ALERTCOMMAND_H

#include "EmergencyCommand.h"
#include "ExternalCommsInterface.h"
#include <string>

/**
 * AlertCommand — Command Pattern: Concrete Command.
 * Encapsulates a "broadcast campus alert" action.
 * The receiver is an ExternalCommsInterface — in production this is a
 * RadioAdapter wrapping the LegacyRadioSystem, demonstrating Command + Adapter.
 * undo() broadcasts an all-clear cancellation.
 */
class AlertCommand : public EmergencyCommand {
private:
    std::string message;
    std::string area;
    ExternalCommsInterface* receiver;

public:
    AlertCommand(ExternalCommsInterface* recv, const std::string& msg);
    ~AlertCommand() override = default;

    void execute() override;
    void undo() override;
    std::string getCommandName() override;
};

#endif // ALERTCOMMAND_H
