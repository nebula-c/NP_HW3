CXX := $(shell root-config --cxx)
CXX_FLAGS := $(shell root-config --cflags)
CXX_FLAGS += -Wall -Wextra -ggdb
LIBRARIES := $(shell root-config --libs)

SRC := ./src
INCLUDE := ./include

PROGRAM = NP_HW3

all: $(PROGRAM)

$(PROGRAM): $(SRC)/*.cpp
	$(CXX) $(CXX_FLAGS) -I$(INCLUDE) $^ -o $@ $(LIBRARIES)
