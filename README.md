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
| [Participant Name] | [Student Number] |
| [Participant Name] | [Student Number] |
| Maeryn Pillay | u25146484 |

## Project Features
CampusGuard demonstrates:
* Registering incidents and tracking their changing operational status
* Dispatching campus security, medical responders, and facilities staff
* Executing building access actions (locking/unlocking doors, restricting areas)
* Operator actions encapsulated as distinct objects (with execution and undo capabilities)
* Automated coordination between response components when an incident changes condition
* Seamless integration with an existing legacy or external communication service
* High-level emergency workflows that require several subsystem operations to execute in sequence
* Dynamic instantiation and configuration of specific responder units
* Sensible handling of invalid operations and failures
* Clean polymorphic object destruction and clear ownership policies

## Design Patterns

### Command
The Command pattern represents operator actions (like dispatching a unit or securing a building) as objects. This separates the creation of the request from its execution and allows commands to be tracked or undone.

### Mediator
The Mediator pattern coordinates the collaborating response components (Security, Medical, Facilities). When a component updates or an incident condition changes, the mediator ensures the necessary departments react without them relying on direct many-to-many dependencies.

### Adapter
The Adapter pattern translates the incompatible interface of an external, legacy city radio system into the modern communications interface that CampusGuard expects to use.

### Facade
The Facade pattern provides high-level entry points for complex, realistic workflows (e.g., initiating a campus evacuation) by coordinating three or more underlying subsystem operations behind a single, simple method call.

### State (Team-Selected)
The State pattern controls the lifecycle of an incident (Reported, Active, Resolved). The behaviour of the incident and the operations permitted depend entirely on its current state, preventing invalid transitions and large switch statements.

### Factory Method (Team-Selected)
The Factory Method pattern decouples the core logic from the complex instantiation and initialisation of response units, allowing the system to spawn specific security, medical, or facility components dynamically.

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
