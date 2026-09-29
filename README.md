# 214-Prac-5-MMA
# CampusGuard

**CampusGuard** is an emergency-response coordination platform developed for COS 214 Practical 5.

The system models a comprehensive incident management network for a large university campus. It allows operators to register emergencies, dispatch security and medical responders, control building access, and broadcast alerts, all while gracefully integrating with external legacy systems and ensuring strict coordination between different departments.

The project is implemented in C++11 and meaningfully demonstrates the following Gang of Four design patterns:
* Command
* Mediator
* Adapter
* Facade
* State
* Factory Method

## Team Members

| Name | Student Number |
| :--- | :--- |
| Angela Ramaboea | u25445392 |
| Matshidiso Dibakoane | u25227506 |
| Maeryn Pillay | u25146484 |

## Project Features
CampusGuard demonstrates:
* Registering incidents and tracking their changing operational status
* Dispatching campus security, medical responders, and facilities staff
* Executing building access actions (locking and unlocking areas)
* Operator actions encapsulated as distinct objects (with execution and undo capabilities)
* Automated coordination between response components when an incident changes condition
* Seamless integration with an existing legacy or external communication service
* High-level emergency workflows that require several subsystem operations to execute in sequence
* Dynamic instantiation and configuration of specific responder units
* Sensible handling of invalid operations and failures
* Clean polymorphic object destruction and clear ownership policies

## Design Patterns

### Command
The Command pattern represents operator actions as objects (`DispatchCommand`, `LockdownCommand`, `AlertCommand`). `OperatorTerminal` (invoker) executes them, records the ones that succeed, supports undo, and prints an audit trail. A command that fails (unknown or unavailable unit) is rejected and not recorded.

### Mediator
`EmergencyMediator` coordinates the response units (`SecurityTeam`, `MedicalResponder`, `FacilitiesStaff`); no unit holds a pointer to another. When `FacilitiesStaff` locks or unlocks an area, the mediator relays the event and security teams secure or leave the perimeter. When an incident changes state, the mediator broadcasts the change and the units on scene react (deploy or stand down).

### Adapter
`RadioAdapter` implements `ExternalCommsInterface::sendAlert(message)` by translating it into the legacy call `LegacyRadioSystem::transmitEmergencySignal(code, description)`, working out the numeric city-radio signal code from the alert text.

### Facade
`CampusGuardFacade::handleChemicalSpill(incident)` runs the full HAZMAT protocol in one call: activate the incident (State), alert the city over the legacy radio (Adapter), call medical crews to the scene (Mediator), and lock the area through the operator terminal (Command). The subsystems remain directly usable; `main` still uses the terminal and incidents directly.

### State (Team-Selected)
`Incident` delegates `escalate()`, `resolve()` and `addNote()` to its current `IncidentState` (`ReportedState` -> `ActiveState` -> `ResolvedState`). Invalid requests (resolving a reported incident, resolving twice, escalating a resolved incident) are rejected with a clear message. Every transition is announced to the mediator, which is how units coordinate when an incident's condition changes.

### Factory Method (Team-Selected)
`ResponseUnitFactory::commissionUnit()` brings a new unit onto the network: it calls the factory method `createResponder()` (overridden by `SecurityFactory`, `MedicalFactory`, `FacilitiesFactory`) and registers the result with the coordinator. New units can be commissioned mid-incident (MED-02 in scenario 2).

## Ownership Policy

| Owner | Owns | Released |
| :--- | :--- | :--- |
| `main` | mediator, terminal, facade, incidents, radio adapter, legacy radio | explicit `delete` at shutdown |
| `EmergencyMediator` | every registered response unit | its destructor |
| `OperatorTerminal` | every command passed to `executeCommand()` | failed commands immediately; undone commands after `undo()`; the rest in its destructor |
| `Incident` | its current `IncidentState` | on each state change and in its destructor |

All other pointers (facade members, command receivers, the adapter's adaptee, each unit's coordinator) are non-owning. Owning classes disable copying.

## Repository Structure

```text
Prac_5/
|
|-- *.cpp                     C++ source files
|-- *.h                       C++ header files
|-- main.cpp                  Program entry point
|-- Makefile                  Project build instructions
|-- Dockerfile                Docker environment configuration
|-- docker-compose.yml        Docker Compose orchestration
|-- README.md                 Project documentation
|
|-- docs/
    |
    |-- diagrams/
        |-- Class Diagram.jpg
        |-- Sequence Diagram (Command).jpg
        |-- Sequence Diagram (Facade).jpg
        |-- Behavioural Diagram (State).jpg
        |-- CampusGuard_UML.xmi
        |-- Debugging Evidence.png
        |-- Valgrind Evidence.png
```
The `docs/diagrams/` directory contains the UML diagrams, project documentation, and debugging evidence used for the practical.

## Building the Project

The final executable is named:
`CampusGuard`

The project can be compiled using:
```bash
make
```

To remove generated object files and the executable:
```bash
make clean
```

To rebuild the complete project:
```bash
make clean
make
```

## Running CampusGuard

After compiling the project locally:
```bash
./CampusGuard
```

## Docker Integration

The project includes a Docker environment configured via `docker-compose.yml` to ensure a consistent execution environment for the assessed demonstration. The image contains all tools required to compile, run, debug, and investigate CampusGuard (including `g++`, `make`, `gdb`, and `valgrind`).

### Run the Assessed Demonstration
As per the practical requirements, the official demonstration must be launched via Docker Compose. From the root directory, run:
```bash
docker compose up --build
```
This will build the image, compile the project using the Makefile, and automatically execute the CampusGuard demonstration.

### Open an Interactive Docker Shell (For Debugging)
To open an interactive shell inside the container to manually run GDB or Valgrind:
```bash
docker run --rm -it --entrypoint /bin/bash campusguard-app
```
*(Note: Replace `campusguard-app` with the image name generated by docker-compose).*

Once inside the container (`/app`), you can compile and run manually:
```bash
make clean
make
./CampusGuard
```

## GDB (Debugging)

GDB is available inside the Docker environment. To open a shell with debugging permissions enabled:
```bash
docker run --rm -it \
  --cap-add=SYS_PTRACE \
  --security-opt seccomp=unconfined \
  --entrypoint /bin/bash campusguard-app
```
Start GDB:
```bash
gdb ./CampusGuard
```
GDB evidence is included in the project documentation to showcase investigation of runtime execution.

## Valgrind (Memory Management)

Valgrind is installed to ensure clean memory management and verify that all polymorphic base classes possess virtual destructors. 

Inside the interactive Docker shell, run:
```bash
valgrind --leak-check=full --show-leak-kinds=all ./CampusGuard
```
The final implementation must show no definitely-lost memory. Valgrind evidence is provided in the documentation.

## UML Documentation

The `docs/diagrams/` directory contains the UML documentation:
* **UML Class Diagram** covering the final system.
* **UML Sequence Diagram** showing a substantial runtime interaction including the Command pattern.
* **UML Sequence Diagram** showing a workflow including the Facade or Adapter.
* **Additional Behavioural Diagram** explaining the State pattern's transitions.

The diagrams reflect the final C++ implementation and trace directly to the runtime behaviour.

## GitHub Workflow

Development is performed collaboratively using Git and GitHub. The repository history demonstrates development over time and meaningful contributions from all three team members. 

* The `main` branch is protected. 
* Team members develop features on separate branches and create Pull Requests before merging.
* Merging requires meaningful commit messages and team coordination.

## Course Information
**Module:** COS 214 Practical 5  
**Project:** CampusGuard - Emergency Response Coordination  
**Language:** C++11
