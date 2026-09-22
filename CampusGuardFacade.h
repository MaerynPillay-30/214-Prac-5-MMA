#ifndef CAMPUSGUARDFACADE_H
#define CAMPUSGUARDFACADE_H

#include <string>

class OperatorTerminal;
class CampusCoordinator;
class ExternalCommsInterface;
class FacilitiesStaff;

/**
 * CampusGuardFacade — Facade Pattern.
 * Provides high-level emergency workflow entry points that hide the
 * complexity of coordinating multiple subsystems. Each method internally
 * coordinates at least three subsystem operations (OperatorTerminal,
 * CampusCoordinator, ExternalCommsInterface) behind a single simple call.
 *
 * The underlying subsystems remain independently usable — clients that
 * need fine-grained control can still call them directly.
 *
 * Ownership: The facade holds non-owning raw pointers; all subsystems
 * are owned by and destroyed by the caller (main.cpp).
 */
class CampusGuardFacade {
private:
    OperatorTerminal*       terminal;
    CampusCoordinator*      mediator;
    ExternalCommsInterface* comms;
    FacilitiesStaff*        facilities; // needed for LockdownCommand receiver

public:
    CampusGuardFacade(OperatorTerminal* term,
                      CampusCoordinator* med,
                      ExternalCommsInterface* c,
                      FacilitiesStaff* fac);
    ~CampusGuardFacade() = default;

    /**
     * Initiates a full campus evacuation workflow:
     *   1. Broadcast evacuation order via external comms (Adapter)
     *   2. Notify all response components via mediator (Mediator)
     *   3. Execute a dispatch command through the terminal (Command)
     */
    void initiateEvacuation();

    /**
     * Activates the HAZMAT chemical spill protocol:
     *   1. Broadcast HAZMAT alert via external comms (Adapter)
     *   2. Coordinate HAZMAT response via mediator (Mediator)
     *   3. Execute lockdown of chemistry wing via terminal (Command)
     */
    void handleChemicalSpill();

    /**
     * Triggers a targeted area lockdown:
     *   1. Broadcast lockdown alert via external comms (Adapter)
     *   2. Notify all components via mediator (Mediator)
     *   3. Execute lockdown command on FacilitiesStaff via terminal (Command)
     */
    void triggerLockdownArea(const std::string& area);

    /**
     * Cancels the last operation:
     *   1. Undo last command via terminal (Command undo)
     *   2. Broadcast stand-down via mediator (Mediator)
     *   3. Send all-clear via external comms (Adapter)
     */
    void cancelOperation();
};

#endif // CAMPUSGUARDFACADE_H
