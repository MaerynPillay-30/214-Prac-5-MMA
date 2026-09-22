/**
 * main.cpp — CampusGuard: Emergency Response Coordination Platform
 *
 * Demonstrates two end-to-end runtime scenarios, each weaving together
 * multiple GoF patterns in a coherent workflow:
 *
 * SCENARIO 1: FIRE AT SCIENCE BUILDING
 *   Patterns visible: Factory Method, State, Command, Mediator, Adapter
 *
 * SCENARIO 2: CHEMICAL SPILL IN CHEMISTRY LAB
 *   Patterns visible: Factory Method, State, Facade (->Command+Mediator+Adapter), State
 *
 * Ownership policy (Valgrind-clean):
 *   - main owns: mediator, radioAdapter, legacyRadio, all responders, terminal, facade
 *   - OperatorTerminal owns: EmergencyCommand* objects in its history
 *   - Incident owns: its current IncidentState*
 *   - Factories create (new) responders; main takes ownership and deletes them
 *   - Facade holds non-owning pointers to all subsystems
 */

#include <iostream>
#include <string>

// Patterns: Mediator
#include "EmergencyMediator.h"

// Patterns: Factory Method
#include "SecurityFactory.h"
#include "MedicalFactory.h"
#include "FacilitiesFactory.h"

// Patterns: Colleagues (cast targets for factory-created responders)
#include "SecurityTeam.h"
#include "MedicalResponder.h"
#include "FacilitiesStaff.h"

// Patterns: Adapter
#include "LegacyRadioSystem.h"
#include "RadioAdapter.h"

// Patterns: Command
#include "OperatorTerminal.h"
#include "DispatchCommand.h"
#include "AlertCommand.h"
#include "LockdownCommand.h"

// Patterns: State
#include "Incident.h"
#include "ReportedState.h"
#include "ActiveState.h"
#include "ResolvedState.h"

// Patterns: Facade
#include "CampusGuardFacade.h"

// Helper: print a bold section separator
static void section(const std::string& title) {
    std::cout << "\n╔══════════════════════════════════════════════════════╗" << std::endl;
    std::cout << "║  " << title << std::endl;
    std::cout << "╚══════════════════════════════════════════════════════╝\n" << std::endl;
}

int main() {
    std::cout << "========================================================" << std::endl;
    std::cout << "  CampusGuard — Emergency Response Coordination System  " << std::endl;
    std::cout << "========================================================\n" << std::endl;

    // ----------------------------------------------------------------
    //  INFRASTRUCTURE SETUP
    //  Create the shared subsystems that both scenarios will use.
    // ----------------------------------------------------------------
    section("SYSTEM INITIALISATION");

    // ----- Mediator (CampusCoordinator) -----
    std::cout << "[Setup] Creating EmergencyMediator..." << std::endl;
    EmergencyMediator* mediator = new EmergencyMediator();

    // ----- Factory Method: create four response units -----
    std::cout << "\n[Setup] Spawning response units via factories..." << std::endl;
    SecurityFactory  secFactory;
    MedicalFactory   medFactory;
    FacilitiesFactory facFactory;

    // Each createResponder call: factory instantiates the correct subtype,
    // and the ResponseComponent constructor self-registers with the mediator.
    SecurityTeam* sec1 = static_cast<SecurityTeam*>(
        secFactory.createResponder(mediator, "SEC-01", "Main Gate"));

    SecurityTeam* sec2 = static_cast<SecurityTeam*>(
        secFactory.createResponder(mediator, "SEC-02", "East Checkpoint"));

    MedicalResponder* med1 = static_cast<MedicalResponder*>(
        medFactory.createResponder(mediator, "MED-01", "Campus Clinic"));

    FacilitiesStaff* fac1 = static_cast<FacilitiesStaff*>(
        facFactory.createResponder(mediator, "FAC-01", "Facilities Hub"));

    // ----- Adapter: wrap legacy radio in the modern interface -----
    std::cout << "\n[Setup] Initialising external comms adapter..." << std::endl;
    LegacyRadioSystem* legacyRadio = new LegacyRadioSystem();
    RadioAdapter*      radioAdapter = new RadioAdapter(legacyRadio);
    radioAdapter->execute(); // confirm radio online

    // ----- Command Invoker -----
    std::cout << "\n[Setup] Creating OperatorTerminal (command invoker)..." << std::endl;
    OperatorTerminal* terminal = new OperatorTerminal();

    // ----- Facade -----
    std::cout << "\n[Setup] Initialising CampusGuardFacade..." << std::endl;
    CampusGuardFacade* facade = new CampusGuardFacade(terminal, mediator,
                                                      radioAdapter, fac1);

    std::cout << "\n[Setup] System ready. All four units registered with mediator." << std::endl;

    // ================================================================
    //  SCENARIO 1: FIRE AT SCIENCE BUILDING
    //  Patterns: Factory Method (already used), State, Command, Mediator, Adapter
    //  This scenario shows a command triggering mediator coordination.
    // ================================================================
    section("SCENARIO 1 — FIRE AT SCIENCE BUILDING");

    // --- State Pattern: Create and transition the incident ---
    std::cout << "--- [State] Registering incident ---" << std::endl;
    Incident* fireIncident = new Incident(
        "Fire reported — smoke visible from third floor",
        "Science Building", 7, "09:14:00");

    fireIncident->changeState(new ReportedState(fireIncident));
    fireIncident->addNotes("Call received from janitor on 3rd floor");

    // Invalid-operation case: try to resolve before activation (requirement 6)
    std::cout << "\n--- [State] Attempting invalid resolve (should be rejected) ---" << std::endl;
    fireIncident->resolve();

    // Valid transition: Reported -> Active
    std::cout << "\n--- [State] Escalating to ACTIVE ---" << std::endl;
    fireIncident->escalate();
    fireIncident->addNotes("Fire brigade on route, two exits blocked by smoke");

    // --- Command Pattern: Dispatch command triggers Mediator coordination ---
    std::cout << "\n--- [Command + Mediator] Dispatching response team ---" << std::endl;
    // The DispatchCommand's receiver is the CampusCoordinator.
    // execute() fires a "DISPATCH:Science Building" event through the mediator,
    // which then notifies all registered colleagues — demonstrating the
    // required "command triggers mediator coordination" sequence.
    terminal->executeCommand(
        new DispatchCommand(mediator, "Science Building"));

    // --- Command + Adapter: Send campus-wide alert via legacy radio ---
    std::cout << "\n--- [Command + Adapter] Broadcasting fire alert ---" << std::endl;
    // AlertCommand receiver is the ExternalCommsInterface (RadioAdapter).
    // sendAlert() is translated inside the adapter to the legacy
    // transmitEmergencySignal(code, description) API.
    terminal->executeCommand(
        new AlertCommand(radioAdapter,
                         "FIRE ALERT — Science Building. Evacuate immediately. Do not use elevators."));

    // --- Command: Lock the affected lab wing ---
    std::cout << "\n--- [Command] Locking Science Lab Wing ---" << std::endl;
    terminal->executeCommand(
        new LockdownCommand(fac1, "Science Building Lab Wing"));

    // --- State: Active incident — redundant escalation handled gracefully ---
    std::cout << "\n--- [State] Redundant escalate while ACTIVE (invalid-op case) ---" << std::endl;
    fireIncident->escalate();

    // --- State: Resolve the incident ---
    std::cout << "\n--- [State] Resolving incident ---" << std::endl;
    fireIncident->resolve();

    // --- State: Attempt to resolve again (invalid — already resolved) ---
    std::cout << "\n--- [State] Attempting second resolve (should be rejected) ---" << std::endl;
    fireIncident->resolve();

    // --- Audit trail after Scenario 1 ---
    terminal->exportAuditTrail();


    // ================================================================
    //  SCENARIO 2: CHEMICAL SPILL IN CHEMISTRY LAB
    //  Patterns: Factory Method (new unit mid-scenario), State,
    //            Facade (internally coordinates Command + Mediator + Adapter)
    //  This scenario demonstrates the Facade hiding subsystem complexity
    //  and at least four patterns in one execution flow.
    // ================================================================
    section("SCENARIO 2 — CHEMICAL SPILL IN CHEMISTRY LAB");

    // --- Factory Method: spawn an additional medical unit mid-scenario ---
    std::cout << "--- [Factory Method] Spawning additional MedicalResponder mid-scenario ---" << std::endl;
    MedicalResponder* med2 = static_cast<MedicalResponder*>(
        medFactory.createResponder(mediator, "MED-02", "North Campus Clinic"));

    // --- State: Register and escalate the chemical spill incident ---
    std::cout << "\n--- [State] Registering chemical spill incident ---" << std::endl;
    Incident* spillIncident = new Incident(
        "Chemical spill — unidentified solvent in laboratory",
        "Chemistry Lab", 9, "14:32:00");

    spillIncident->changeState(new ReportedState(spillIncident));
    spillIncident->addNotes("Level 3 biohazard. Evacuation of block C underway.");
    spillIncident->escalate(); // Reported -> Active

    // --- Facade: handleChemicalSpill hides the 3-subsystem workflow ---
    // Internally: (1) comms.sendAlert [Adapter]
    //             (2) mediator.notify("CHEMICAL_SPILL") [Mediator]
    //             (3) terminal.executeCommand(LockdownCommand) [Command]
    std::cout << "\n--- [Facade] Activating chemical spill protocol ---" << std::endl;
    facade->handleChemicalSpill();

    // --- Direct subsystem use: MedicalResponder provides triage (still usable) ---
    std::cout << "--- [Direct subsystem] Medical unit performing triage ---" << std::endl;
    med1->assessTriage();
    med1->provideFirstAid();
    med2->reportCasualties(3);

    // --- Facade: cancelOperation — undo, notify, broadcast all-clear ---
    std::cout << "--- [Facade] Cancelling last operation (Lockdown of Chemistry Lab Wing) ---" << std::endl;
    facade->cancelOperation();

    // --- State: Resolve the spill incident ---
    std::cout << "\n--- [State] Resolving chemical spill incident ---" << std::endl;
    spillIncident->addNotes("Spill contained. Ventilation restored.");
    spillIncident->resolve();

    // --- Command: demonstrate undo on an alert command ---
    std::cout << "\n--- [Command] Operator sends another alert then immediately undoes it ---" << std::endl;
    terminal->executeCommand(
        new AlertCommand(radioAdapter, "SECONDARY HAZMAT WARNING — North Block"));
    terminal->undoLastCommand(); // sends ALL CLEAR via adapter

    // --- Undo when history empty (invalid-op handling) ---
    std::cout << "\n--- [Command] Attempting undo with empty history (invalid-op case) ---" << std::endl;
    // First drain remaining commands by undoing them all
    terminal->undoLastCommand();
    terminal->undoLastCommand();
    terminal->undoLastCommand();
    terminal->undoLastCommand();
    // Now history is empty — next undo should be rejected gracefully
    terminal->undoLastCommand();

    // --- Final audit trail ---
    terminal->exportAuditTrail();

    // ================================================================
    //  SHUTDOWN — Explicit, ordered cleanup (Valgrind-clean)
    // ================================================================
    section("SYSTEM SHUTDOWN");
    std::cout << "[Shutdown] Releasing all resources..." << std::endl;

    // Incidents own their states — must be deleted before the mediator
    delete spillIncident;
    delete fireIncident;

    // Facade holds non-owning pointers — delete first (no-op for owned objects)
    delete facade;

    // OperatorTerminal owns remaining commands in history
    delete terminal;

    // Response components are owned by main (created by factories)
    // Delete before the mediator (components hold a pointer to it but
    // the default destructor never dereferences it)
    delete med2;
    delete fac1;
    delete med1;
    delete sec2;
    delete sec1;

    // Mediator holds only non-owning pointers — delete after colleagues
    delete mediator;

    // Adapter wraps but does not own the legacy system
    delete radioAdapter;
    delete legacyRadio;

    std::cout << "[Shutdown] CampusGuard terminated cleanly." << std::endl;
    std::cout << "\n========================================================" << std::endl;
    std::cout << "  All six GoF patterns demonstrated across two scenarios." << std::endl;
    std::cout << "========================================================" << std::endl;

    return 0;
}
