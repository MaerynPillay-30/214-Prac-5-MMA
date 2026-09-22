#ifndef LOCKDOWNCOMMAND_H
#define LOCKDOWNCOMMAND_H

#include "EmergencyCommand.h"
#include <string>

class FacilitiesStaff; // forward declaration

/**
 * LockdownCommand — Command Pattern: Concrete Command.
 * Encapsulates a "lock a specific campus area" action.
 * The receiver is a FacilitiesStaff unit which owns the physical
 * access-control capability. undo() lifts the lockdown.
 */
class LockdownCommand : public EmergencyCommand {
private:
    FacilitiesStaff* receiver;
    std::string area;

public:
    LockdownCommand(FacilitiesStaff* recv, const std::string& s);
    ~LockdownCommand() override = default;

    void execute() override;
    void undo() override;
    std::string getCommandName() override;
};

#endif // LOCKDOWNCOMMAND_H
