#ifndef EMERGENCYCOMMAND_H
#define EMERGENCYCOMMAND_H

#include <string>

/**
 * EmergencyCommand — Command Pattern: Abstract Command interface.
 * All operator actions (dispatch, alert, lockdown) are encapsulated as
 * EmergencyCommand objects, decoupling the invoker (OperatorTerminal)
 * from the receivers (CampusCoordinator, ExternalCommsInterface, FacilitiesStaff).
 */
class EmergencyCommand {
public:
    EmergencyCommand() = default;
    virtual ~EmergencyCommand() = default;

    virtual void execute() = 0;
    virtual void undo() = 0;
    virtual std::string getCommandName() = 0;
};

#endif // EMERGENCYCOMMAND_H
