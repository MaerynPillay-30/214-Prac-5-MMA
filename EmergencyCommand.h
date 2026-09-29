#ifndef EMERGENCYCOMMAND_H
#define EMERGENCYCOMMAND_H

#include <string>

/**
 * EmergencyCommand — Command Pattern: abstract Command.
 *
 * Every operator action (dispatch a unit, lock an area, issue an alert) is an
 * EmergencyCommand object, so the invoker (OperatorTerminal) never needs to
 * know the receivers. execute() returns false when the action could not be
 * carried out; the terminal then does not record it in the history.
 */
class EmergencyCommand {
public:
    EmergencyCommand() {}
    virtual ~EmergencyCommand() {}

    virtual bool execute() = 0;
    virtual void undo() = 0;
    virtual std::string getCommandName() const = 0;
};

#endif // EMERGENCYCOMMAND_H
