#include "CampusGuardFacade.h"
#include "OperatorTerminal.h"
#include "CampusCoordinator.h"
#include "ExternalCommsInterface.h"
#include "LockdownCommand.h"
#include "Incident.h"
#include <iostream>
#include <string>

CampusGuardFacade::CampusGuardFacade(OperatorTerminal* term, CampusCoordinator* med,
                                     ExternalCommsInterface* c, FacilitiesStaff* fac)
    : terminal(term), mediator(med), comms(c), facilities(fac) {}

void CampusGuardFacade::handleChemicalSpill(Incident* spill) {
    const std::string area = spill->getLocation();
    std::cout << "\n[Facade] ======== HAZMAT PROTOCOL: " << area << " ========" << std::endl;

    std::cout << "[Facade] Step 1/4: Activate the incident" << std::endl;
    spill->escalate();

    std::cout << "[Facade] Step 2/4: Alert the city over the legacy radio" << std::endl;
    comms->sendAlert("HAZMAT ALERT — chemical spill at " + area + ". Keep clear.");

    std::cout << "[Facade] Step 3/4: Call medical crews to the scene" << std::endl;
    mediator->broadcast("HAZMAT:" + area);

    std::cout << "[Facade] Step 4/4: Lock down the area" << std::endl;
    terminal->executeCommand(new LockdownCommand(facilities, area));

    std::cout << "[Facade] ======== HAZMAT protocol complete ========\n" << std::endl;
}
