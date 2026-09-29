#ifndef CAMPUSGUARDFACADE_H
#define CAMPUSGUARDFACADE_H

class OperatorTerminal;
class CampusCoordinator;
class ExternalCommsInterface;
class FacilitiesStaff;
class Incident;

/**
 * CampusGuardFacade — Facade Pattern.
 *
 * One call for a workflow that would otherwise need the client to drive four
 * subsystems in the right order. The subsystems stay public: main still uses
 * the terminal, commands and incidents directly where fine control is needed.
 *
 * Ownership: holds NON-owning pointers; every subsystem is owned by main.
 */
class CampusGuardFacade {
private:
    OperatorTerminal*       terminal;   // not owned
    CampusCoordinator*      mediator;   // not owned
    ExternalCommsInterface* comms;      // not owned
    FacilitiesStaff*        facilities; // not owned

public:
    CampusGuardFacade(OperatorTerminal* term, CampusCoordinator* med,
                      ExternalCommsInterface* c, FacilitiesStaff* fac);
    ~CampusGuardFacade() {}

    /**
     * HAZMAT protocol for a reported chemical spill:
     *   1. activate the incident                 (State -> Mediator)
     *   2. send a HAZMAT alert off campus         (Adapter)
     *   3. call all medical crews to the scene    (Mediator)
     *   4. lock the area through the terminal     (Command -> FacilitiesStaff -> Mediator)
     */
    void handleChemicalSpill(Incident* spill);
};

#endif // CAMPUSGUARDFACADE_H
