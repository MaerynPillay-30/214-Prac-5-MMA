CXX      = g++
CXXFLAGS = -std=c++11 -Wall -Wextra -g
TARGET   = CampusGuard

SRCS = main.cpp \
       Incident.cpp \
       ReportedState.cpp \
       ActiveState.cpp \
       ResolvedState.cpp \
       ResponseComponent.cpp \
       SecurityTeam.cpp \
       MedicalResponder.cpp \
       FacilitiesStaff.cpp \
       EmergencyMediator.cpp \
       ResponseUnitFactory.cpp \
       SecurityFactory.cpp \
       MedicalFactory.cpp \
       FacilitiesFactory.cpp \
       LegacyRadioSystem.cpp \
       RadioAdapter.cpp \
       OperatorTerminal.cpp \
       DispatchCommand.cpp \
       AlertCommand.cpp \
       LockdownCommand.cpp \
       CampusGuardFacade.cpp

OBJS = $(SRCS:.cpp=.o)

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $^

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

run: $(TARGET)
	./$(TARGET)

valgrind: $(TARGET)
	valgrind --leak-check=full --show-leak-kinds=all ./$(TARGET)

clean:
	rm -f $(OBJS) $(TARGET)

.PHONY: all run valgrind clean
