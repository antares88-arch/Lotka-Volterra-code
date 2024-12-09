
CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra

TARGET = predatori_prede_simulazione
TEST_TARGET = test_simulazione

SRC = main.cpp Ambiente.cpp
TEST_SRC = tests.cpp Ambiente.cpp
all: $(TARGET)

$(TARGET): $(SRC)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(SRC)


test: $(TEST_SRC)
	$(CXX) $(CXXFLAGS) -o $(TEST_TARGET) $(TEST_SRC)

clean:
	rm -f $(TARGET) $(TEST_TARGET)

