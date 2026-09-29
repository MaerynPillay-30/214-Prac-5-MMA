# 214-Prac-5-MMA

# CampusGuard

**CampusGuard** is an emergency-response coordination platform developed for COS 214 Practical 5.

The system models incident management for a large university campus. Operators register emergencies, dispatch security, medical and facilities units, lock and unlock campus areas, and send alerts over the city's legacy radio network. Response units coordinate through a central mediator instead of depending on one another directly.

The project is implemented in C++11 and uses the following Gang of Four design patterns:

* Command
* Mediator
* Adapter
* Facade
* State (team-selected)
* Factory Method (team-selected)

## Team Members

| Name | Student Number |
| :--- | :--- |
| Angela Ramaboea | u25445392 |
| Matshidiso Dibakoane | u25227506 |
| Maeryn Pillay | u25146484 |

## Project Features

CampusGuard demonstrates:

* Registering incidents and tracking their status (Reported, Active, Resolved)
* Dispatching security, medical and facilities units, with availability checks
* Building-access actions (locking and unlocking areas)
* Operator actions as command objects, with undo and an audit trail
* Coordination between response units when an incident changes state or an area is locked
* Integration with a legacy city radio system whose interface does not match CampusGuard's
* A multi-step HAZMAT workflow behind a single facade call
* Commissioning new response units at runtime through factories
* Sensible handling of invalid operations and failures
* Clean polymorphic destruction and a clear ownership policy (Valgrind clean)

## Design Patterns

### Command
Operator actions are objects: `DispatchCommand`, `LockdownCommand` and `AlertCommand`, all derived from `EmergencyCommand`. `OperatorTerminal` (the invoker) executes them, records the ones that succeed, supports undo, and prints an audit trail. A command that fails (unknown or unavailable unit) is rejected and not recorded.

### Mediator
`EmergencyMediator` (implementing `CampusCoordinator`) coordinates the response units: `SecurityTeam`, `MedicalResponder` and `FacilitiesStaff`. No unit holds a pointer to another. When `FacilitiesStaff` locks or unlocks an area, the mediator relays the event and security teams secure or leave the perimeter. When an incident changes state, the mediator broadcasts the change and the units on scene deploy or stand down.

### Adapter
`RadioAdapter` implements `ExternalCommsInterface::sendAlert(message)` by translating it into the legacy call `LegacyRadioSystem::transmitEmergencySignal(code, description)`. It works out the numeric city-radio signal code from the alert text (for example 101 for fire, 202 for HAZMAT, 0 for all-clear).

### Facade
`CampusGuardFacade::handleChemicalSpill(incident)` runs the full HAZMAT protocol in one call:

1. Activate the incident (State, then Mediator).
2. Alert the city over the legacy radio (Adapter).
3. Call medical crews to the scene (Mediator).
4. Lock the area through the operator terminal (Command, then FacilitiesStaff, then Mediator).

The subsystems remain directly usable: `main` still uses the terminal, commands and incidents directly.

### State (Team-Selected)
`Incident` delegates `escalate()`, `resolve()` and `addNote()` to its current `IncidentState` (`ReportedState` → `ActiveState` → `ResolvedState`). Invalid requests are rejected with a clear message: resolving a reported incident, resolving twice, or escalating a resolved incident. Every transition is announced to the mediator, which is how units coordinate when an incident's condition changes.

### Factory Method (Team-Selected)
`ResponseUnitFactory::commissionUnit()` brings a new unit onto the network. It calls the factory method `createResponder()`, which is overridden by `SecurityFactory`, `MedicalFactory` and `FacilitiesFactory`, and registers the result with the coordinator. New units can be commissioned mid-incident (MED-02 in scenario 2).

## Demonstration Scenarios

`main.cpp` runs two end-to-end stories.

**Scenario 1: Fire at the Science Building.** Uses Factory Method, State, Command, Mediator and Adapter.

1. The incident is registered.
2. An early resolve is rejected.
3. The incident is activated, and facilities opens the emergency exits.
4. SEC-01 and MED-01 are dispatched. The ambulance is then cancelled with undo.
5. A fire alert goes out over the legacy radio.
6. The lab wing is locked, so SEC-02 secures the perimeter through the mediator.
7. Dispatching the unknown unit SEC-99 is refused.
8. The lockdown is lifted.
9. The incident is resolved and the units stand down.
10. A second resolve is rejected.

**Scenario 2: Chemical spill in the Chemistry Lab.** Uses Factory Method, State, Facade, Adapter, Mediator and Command.

1. MED-02 is commissioned.
2. The spill is registered.
3. `handleChemicalSpill()` runs the four-step HAZMAT protocol.
4. Dispatching the busy SEC-01 is refused.
5. A secondary warning is sent and then retracted with undo.
6. The lockdown is lifted.
7. The spill is resolved.

## Ownership Policy

| Owner | Owns | Released |
| :--- | :--- | :--- |
| `main` | mediator, terminal, facade, incidents, radio adapter, legacy radio | explicit `delete` at shutdown |
| `EmergencyMediator` | every registered response unit | its destructor |
| `OperatorTerminal` | every command passed to `executeCommand()` | failed commands immediately; undone commands after `undo()`; the rest in its destructor |
| `Incident` | its current `IncidentState` | on each state change and in its destructor |

All other pointers are non-owning: the facade's members, command receivers, the adapter's adaptee, and each unit's and incident's coordinator. Owning classes disable copying. Every polymorphic base class has a virtual destructor.

## Repository Structure

```text
214-Prac-5-MMA/
|
|-- main.cpp                      Program entry point (two demo scenarios)
|
|-- Command:        EmergencyCommand.h, DispatchCommand.*, LockdownCommand.*,
|                   AlertCommand.*, OperatorTerminal.*
|-- Mediator:       CampusCoordinator.h, EmergencyMediator.*, ResponseComponent.*,
|                   SecurityTeam.*, MedicalResponder.*, FacilitiesStaff.*
|-- Adapter:        ExternalCommsInterface.h, RadioAdapter.*, LegacyRadioSystem.*
|-- Facade:         CampusGuardFacade.*
|-- State:          Incident.*, IncidentState.h, ReportedState.*, ActiveState.*,
|                   ResolvedState.*
|-- Factory Method: ResponseUnitFactory.*, SecurityFactory.*, MedicalFactory.*,
|                   FacilitiesFactory.*
|
|-- Makefile                      Build rules (all, run, valgrind, clean)
|-- Dockerfile                    Build/run image (g++, make, gdb, valgrind)
|-- docker-compose.yml            Docker Compose service for the demonstration
|-- .gitignore / .dockerignore    Keep build output out of Git and the Docker image
|-- README.md                     Project documentation
|
|-- docs/
    |-- Practical 5 Diagrams.docx
    |-- Class Diagram.png
    |-- Sequence diagram 1_ Command + Mediator.png
    |-- Sequence diagram 2_ Facade + Adapter + Mediator + Command (Chemical Spill).png
    |-- State Diagram.png
    |-- GDB Evidence.png
    |-- Valgrind Evidence.png
```

The `docs/` directory contains the UML diagrams and the GDB and Valgrind evidence for the practical.

## Building the Project

The final executable is named `CampusGuard`.

```bash
make            # compile
make run        # compile and run
make valgrind   # compile and run under Valgrind
make clean      # remove object files and the executable
```

## Running CampusGuard

After compiling locally:

```bash
./CampusGuard
```

A successful run ends with:

```text
All resources released. CampusGuard shut down cleanly.
```

## Docker Integration

The Docker image contains everything needed to compile, run, debug and investigate CampusGuard: `g++`, `make`, `gdb` and `valgrind`.

### Run the Assessed Demonstration

The official demonstration is launched with Docker Compose. From the repository root, run:

```bash
docker compose up --build
```

This builds the image, compiles the project with the Makefile, and runs the CampusGuard demonstration.

### Open an Interactive Docker Shell

The Compose file tags the image as `campusguard-app`. To open a shell inside it:

```bash
docker run --rm -it campusguard-app bash
```

Inside the container (`/app`) you can rebuild and run manually:

```bash
make clean
make
./CampusGuard
```

## GDB (Debugging)

GDB needs extra permissions inside a container. Open a debugging shell with:

```bash
docker run --rm -it --cap-add=SYS_PTRACE --security-opt seccomp=unconfined campusguard-app bash
```

Then start GDB:

```bash
gdb ./CampusGuard
```

Our GDB investigation of a real execution bug is included in `docs/`.

## Valgrind (Memory Management)

Inside the Docker shell, run:

```bash
valgrind --leak-check=full --show-leak-kinds=all ./CampusGuard
```

or simply `make valgrind`. The final implementation reports:

```text
All heap blocks were freed -- no leaks are possible
ERROR SUMMARY: 0 errors from 0 contexts
```

The Valgrind evidence is included in `docs/`.

## UML Documentation

The `docs/` directory contains:

* **UML Class Diagram** of the final system
* **Sequence Diagram 1:** dispatch command (Command + Mediator)
* **Sequence Diagram 2:** HAZMAT protocol (Facade + Adapter + State + Mediator + Command)
* **State Diagram:** the Incident lifecycle (State pattern)

Every message and relationship in the diagrams can be traced to the final C++ implementation.

## GitHub Workflow

Development was done collaboratively with Git and GitHub. The repository history shows development over time and contributions from all three team members.

* Team members developed on separate branches (for example `dev`) and merged into `main` through pull requests.
* Commits use meaningful messages, and merges were coordinated within the team.

## Course Information

**Module:** COS 214 Practical 5
**Project:** CampusGuard: Emergency Response Coordination
**Language:** C++11
