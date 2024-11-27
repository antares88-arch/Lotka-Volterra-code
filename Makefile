# Compiler and flags
CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra

# Target executable names
TARGET = predator_prey_simulation
TEST_TARGET = test_simulation

# Source files for the main program
SRC = main.cpp Grid.cpp

# Source files for the unit tests
TEST_SRC = tests.cpp Grid.cpp

# Default target to build the main program
all: $(TARGET)

# Build the main program
$(TARGET): $(SRC)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(SRC)

# Build the unit tests
test: $(TEST_SRC)
	$(CXX) $(CXXFLAGS) -o $(TEST_TARGET) $(TEST_SRC)

# Clean up compiled files
clean:
	rm -f $(TARGET) $(TEST_TARGET)

