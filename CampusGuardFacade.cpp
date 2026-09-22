#include "CampusGuardFacade.h"
#include "OperatorTerminal.h"
#include "CampusCoordinator.h"
#include "ExternalCommsInterface.h"
#include "FacilitiesStaff.h"
#include "DispatchCommand.h"
#include "AlertCommand.h"
#include "LockdownCommand.h"
#include <iostream>

CampusGuardFacade::CampusGuardFacade(OperatorTerminal*       term,
                                     CampusCoordinator*      med,
                                     ExternalCommsInterface* c,
                                     FacilitiesStaff*        fac)
    : terminal(term), mediator(med), comms(c), facilities(fac) {}

// ---------------------------------------------------------------------------
// initiateEvacuation
// Coordinates: ExternalCommsInterface (Adapter) + CampusCoordinator (Mediator)
//              + OperatorTerminal+DispatchCommand (Command)
// ---------------------------------------------------------------------------
void CampusGuardFacade::initiateEvacuation() {
    std::cout << "\n[Facade] ============ EVACUATION PROTOCOL ============" << std::endl;

    // Subsystem 1 — Adapter: broadcast over legacy radio
    std::cout << "[Facade] Step 1: Broadcasting evacuation order via external comms." << std::endl;
    comms->sendAlert("CAMPUS EVACUATION ORDER — All personnel evacuate immediately");

    // Subsystem 2 — Mediator: notify all response components to mobilise
    std::cout << "[Facade] Step 2: Notifying all response components via mediator." << std::endl;
    mediator->notify(nullptr, "EVACUATE_NOW");

    // Subsystem 3 — Command: dispatch all units to assembly point
    std::cout << "[Facade] Step 3: Dispatching all units to assembly point (Command)." << std::endl;
    terminal->executeCommand(new DispatchCommand(mediator, "South Assembly Point"));

    std::cout << "[Facade] ============ Evacuation protocol complete ============\n" << std::endl;
}

// ---------------------------------------------------------------------------
// handleChemicalSpill
// Coordinates: ExternalCommsInterface (Adapter) + CampusCoordinator (Mediator)
//              + OperatorTerminal+LockdownCommand (Command)
// ---------------------------------------------------------------------------
void CampusGuardFacade::handleChemicalSpill() {
    std::cout << "\n[Facade] ============ CHEMICAL SPILL PROTOCOL ============" << std::endl;

    // Subsystem 1 — Adapter: broadcast HAZMAT alert over legacy radio
    std::cout << "[Facade] Step 1: Broadcasting HAZMAT alert via external comms (Adapter)." << std::endl;
    comms->sendAlert("HAZMAT ALERT — Chemical spill in Chemistry Lab. Do not enter.");

    // Subsystem 2 — Mediator: coordinate all components to HAZMAT protocol
    std::cout << "[Facade] Step 2: Coordinating HAZMAT response via mediator." << std::endl;
    mediator->notify(nullptr, "CHEMICAL_SPILL");

    // Subsystem 3 — Command: lock down the chemistry wing via terminal
    std::cout << "[Facade] Step 3: Locking Chemistry Lab Wing (Command -> FacilitiesStaff)." << std::endl;
    terminal->executeCommand(new LockdownCommand(facilities, "Chemistry Lab Wing"));

    std::cout << "[Facade] ============ Chemical spill protocol complete ============\n" << std::endl;
}

// ---------------------------------------------------------------------------
// triggerLockdownArea
// Coordinates: ExternalCommsInterface (Adapter) + CampusCoordinator (Mediator)
//              + OperatorTerminal+LockdownCommand (Command)
// ---------------------------------------------------------------------------
void CampusGuardFacade::triggerLockdownArea(const std::string& area) {
    std::cout << "\n[Facade] ============ AREA LOCKDOWN: " << area
              << " ============" << std::endl;

    // Subsystem 1 — Adapter: broadcast lockdown alert
    std::cout << "[Facade] Step 1: Broadcasting lockdown alert via external comms." << std::endl;
    comms->sendAlert("LOCKDOWN IN EFFECT: " + area + " — Do not enter");

    // Subsystem 2 — Mediator: notify all components about the lockdown
    std::cout << "[Facade] Step 2: Notifying all response components of lockdown." << std::endl;
    mediator->notify(nullptr, "LOCKDOWN:" + area);

    // Subsystem 3 — Command: physically lock the area via FacilitiesStaff
    std::cout << "[Facade] Step 3: Executing LockdownCommand on FacilitiesStaff." << std::endl;
    terminal->executeCommand(new LockdownCommand(facilities, area));

    std::cout << "[Facade] ============ Lockdown complete ============\n" << std::endl;
}

// ---------------------------------------------------------------------------
// cancelOperation
// Coordinates: OperatorTerminal (Command undo) + CampusCoordinator (Mediator)
//              + ExternalCommsInterface (Adapter)
// ---------------------------------------------------------------------------
void CampusGuardFacade::cancelOperation() {
    std::cout << "\n[Facade] ============ CANCEL LAST OPERATION ============" << std::endl;

    // Subsystem 1 — Command: undo the last executed command
    std::cout << "[Facade] Step 1: Undoing last command via OperatorTerminal." << std::endl;
    terminal->undoLastCommand();

    // Subsystem 2 — Mediator: broadcast stand-down to all components
    std::cout << "[Facade] Step 2: Broadcasting STAND_DOWN via mediator." << std::endl;
    mediator->notify(nullptr, "STAND_DOWN");

    // Subsystem 3 — Adapter: broadcast all-clear over legacy radio
    std::cout << "[Facade] Step 3: Broadcasting ALL CLEAR via external comms." << std::endl;
    comms->sendAlert("ALL CLEAR — Previous operation has been cancelled. Stand down.");

    std::cout << "[Facade] ============ Cancellation complete ============\n" << std::endl;
}
