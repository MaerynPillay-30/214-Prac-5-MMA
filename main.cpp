/**
 * main.cpp — CampusGuard: Emergency Response Coordination Platform
 *
 * Two end-to-end runtime stories:
 *
 *   SCENARIO 1 — Fire at the Science Building
 *     Factory Method, State, Command, Mediator, Adapter
 *
 *   SCENARIO 2 — Chemical spill in the Chemistry Lab
 *     Factory Method, State, Facade (-> State + Adapter + Mediator + Command)
 *
 * Ownership policy (Valgrind-clean):
 *   - main owns:             mediator, terminal, facade, incidents,
 *                            radio adapter and legacy radio system
 *   - EmergencyMediator owns: every response unit registered with it
 *                            (units are created by the factories)
 *   - OperatorTerminal owns:  every command passed to executeCommand()
 *   - Incident owns:          its current IncidentState
 *   - Everything else (facade members, command receivers, the adapter's
 *     adaptee, units' coordinator pointer) is a non-owning pointer.
 */

#include <iostream>
#include <string>

#include "EmergencyMediator.h"
#include "SecurityFactory.h"
#include "MedicalFactory.h"
#include "FacilitiesFactory.h"
#include "FacilitiesStaff.h"
#include "LegacyRadioSystem.h"
#include "RadioAdapter.h"
#include "OperatorTerminal.h"
#include "DispatchCommand.h"
#include "AlertCommand.h"
#include "LockdownCommand.h"
#include "Incident.h"
#include "CampusGuardFacade.h"

static void section(const std::string& title) {
    std::cout << "\n======================================================" << std::endl;
    std::cout << "  " << title << std::endl;
    std::cout << "======================================================\n" << std::endl;
}

static void step(const std::string& text) {
    std::cout << "\n--- " << text << " ---" << std::endl;
}

int main() {
    section("CAMPUSGUARD — SYSTEM START-UP");

    step("[Mediator] Creating the coordination network");
    EmergencyMediator* mediator = new EmergencyMediator();

    step("[Factory Method] Commissioning response units");
    SecurityFactory   securityFactory;
    MedicalFactory    medicalFactory;
    FacilitiesFactory facilitiesFactory;

    securityFactory.commissionUnit(mediator, "SEC-01", "Main Gate");
    securityFactory.commissionUnit(mediator, "SEC-02", "East Checkpoint");
    medicalFactory.commissionUnit(mediator, "MED-01", "Campus Clinic");
    // The facilities unit is also the receiver of LockdownCommand, which needs
    // the building-access operations, so the client keeps a typed pointer to it.
    FacilitiesStaff* facilities = static_cast<FacilitiesStaff*>(
        facilitiesFactory.commissionUnit(mediator, "FAC-01", "Facilities Hub"));

    step("[Adapter] Connecting to the city's legacy radio network");
    LegacyRadioSystem* legacyRadio = new LegacyRadioSystem();
    RadioAdapter*      radio       = new RadioAdapter(legacyRadio);
    std::cout << "  RadioAdapter ready (ExternalCommsInterface -> LegacyRadioSystem)" << std::endl;

    step("[Command] Opening the operator terminal");
    OperatorTerminal* terminal = new OperatorTerminal();

    step("[Facade] Wiring the emergency operations facade");
    CampusGuardFacade* facade = new CampusGuardFacade(terminal, mediator, radio, facilities);

    mediator->printRoster();

    // =================================================================
    //  SCENARIO 1 — FIRE AT THE SCIENCE BUILDING
    // =================================================================
    section("SCENARIO 1 — FIRE AT THE SCIENCE BUILDING");

    step("[State] Operator registers the incident");
    Incident* fire = new Incident(mediator, "Smoke on the third floor",
                                  "Science Building", 6, "09:14");
    fire->addNote("Call received from the third-floor janitor");

    step("[State] Invalid: trying to resolve before any response");
    fire->resolve();

    step("[State + Mediator] Incident activated -> units react to the change");
    fire->escalate();

    step("[Command + Mediator] Dispatch security and a medical crew");
    terminal->executeCommand(new DispatchCommand(mediator, "SEC-01", "Science Building"));
    terminal->executeCommand(new DispatchCommand(mediator, "MED-01", "Science Building"));

    step("[Command] No casualties reported — operator cancels the ambulance (undo)");
    terminal->undoLastCommand();

    step("[Command + Adapter] Fire alert over the legacy radio");
    terminal->executeCommand(new AlertCommand(radio,
        "FIRE ALERT — Science Building. Evacuate. Do not use the lifts."));

    step("[Command -> Mediator] Lock the lab wing; security coordinates via the mediator");
    terminal->executeCommand(new LockdownCommand(facilities, "Science Building Lab Wing"));

    step("[Command] Invalid: dispatching a unit that does not exist");
    terminal->executeCommand(new DispatchCommand(mediator, "SEC-99", "Science Building"));

    step("[State] Fire spreads — escalate the active incident");
    fire->escalate();

    mediator->printRoster();

    step("[Command -> Mediator] Fire out — lift the lab wing lockdown (undo)");
    terminal->undoLastCommand();

    step("[State + Mediator] Resolve the fire; units still on scene stand down");
    fire->resolve();

    step("[State] Invalid: resolving a second time");
    fire->resolve();

    terminal->exportAuditTrail();

    // =================================================================
    //  SCENARIO 2 — CHEMICAL SPILL IN THE CHEMISTRY LAB
    // =================================================================
    section("SCENARIO 2 — CHEMICAL SPILL IN THE CHEMISTRY LAB");

    step("[Factory Method] Commissioning an extra medical crew for the afternoon shift");
    medicalFactory.commissionUnit(mediator, "MED-02", "North Campus Clinic");

    step("[State] Operator registers the spill");
    Incident* spill = new Incident(mediator, "Unidentified solvent spilled in a teaching lab",
                                   "Chemistry Lab", 8, "14:32");
    spill->addNote("Three students report dizziness");

    step("[Facade] One call runs the whole HAZMAT protocol");
    facade->handleChemicalSpill(spill);

    mediator->printRoster();

    step("[Command] Invalid: dispatching SEC-01, which is guarding the spill");
    terminal->executeCommand(new DispatchCommand(mediator, "SEC-01", "North Block"));

    step("[Command + Adapter] Operator sends a warning, then retracts it (undo)");
    terminal->executeCommand(new AlertCommand(radio,
        "SECONDARY HAZMAT WARNING — North Block"));
    terminal->undoLastCommand();

    step("[Command -> Mediator] Spill contained — lift the lockdown (undo)");
    spill->addNote("Spill neutralised, ventilation restored");
    terminal->undoLastCommand();

    step("[State + Mediator] Resolve the spill; remaining units stand down");
    spill->resolve();

    mediator->printRoster();
    terminal->exportAuditTrail();

    // =================================================================
    //  SHUTDOWN
    // =================================================================
    section("CAMPUSGUARD — SHUTDOWN");

    delete facade;      // non-owning: frees nothing else
    delete terminal;    // frees the commands left in its history
    delete spill;       // frees its current state
    delete fire;
    delete mediator;    // frees every registered response unit
    delete radio;       // non-owning adapter
    delete legacyRadio;

    std::cout << "All resources released. CampusGuard shut down cleanly." << std::endl;
    return 0;
}
