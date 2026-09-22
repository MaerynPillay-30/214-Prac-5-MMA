CXX      = g++
CXXFLAGS = -std=c++11 -Wall -Wextra -g
TARGET   = CampusGuard

SRCS = main.cpp \
       IncidentState.cpp \
       Incident.cpp \
       ReportedState.cpp \
       ActiveState.cpp \
       ResolvedState.cpp \
       ResponseComponent.cpp \
       EmergencyMediator.cpp \
       SecurityTeam.cpp \
       MedicalResponder.cpp \
       FacilitiesStaff.cpp \
       LegacyRadioSystem.cpp \
       RadioAdapter.cpp \
       SecurityFactory.cpp \
       MedicalFactory.cpp \
       FacilitiesFactory.cpp \
       OperatorTerminal.cpp \
       DispatchCommand.cpp \
       AlertCommand.cpp \
       LockdownCommand.cpp \
       CampusGuardFacade.cpp

OBJS = $(SRCS:.cpp=.o)

# Default target: compile everything
all: $(TARGET)

$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $^

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Remove generated files
clean:
	rm -f $(OBJS) $(TARGET)

.PHONY: all clean
