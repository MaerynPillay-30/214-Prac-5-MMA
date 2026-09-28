#ifndef LOCKDOWNCOMMAND_H
#define LOCKDOWNCOMMAND_H

#include "EmergencyCommand.h"
#include <string>

class FacilitiesStaff;

/**
 * LockdownCommand — Command Pattern: Concrete Command.
 *
 * "Lock this area." The receiver is FacilitiesStaff, which controls building
 * access. Locking raises an AREA_LOCKED event through the mediator, so the
 * command indirectly makes SecurityTeam units coordinate. undo() unlocks it.
 *
 * Ownership: the receiver is NOT owned.
 */
class LockdownCommand : public EmergencyCommand {
private:
    FacilitiesStaff* receiver; // not owned
    std::string area;

public:
    LockdownCommand(FacilitiesStaff* recv, const std::string& area);
    ~LockdownCommand() override {}

    bool execute() override;
    void undo() override;
    std::string getCommandName() const override;
};

#endif // LOCKDOWNCOMMAND_H
