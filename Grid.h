#include <iostream>
#include <cassert>
#include "Grid.h"  // Include the Grid class

void testInitialization() {
    // Create a small 2x2 grid with certain initial population densities
    Grid grid(2, 2, 0.1, 0.02, 0.02, 0.01, 0.02, 0.05, 0.1, 10, 10, 10);

    // Check the initial population in grid cell (0, 0)
    double prey = grid.getPrey(0, 0);
    double predators = grid.getPredators(0, 0);
    double scavengers = grid.getScavengers(0, 0);

    // We don't know the exact values, but they should be in the range [0, density]
    assert(prey >= 0 && prey <= 10);
    assert(predators >= 0 && predators <= 10);
    assert(scavengers >= 0 && scavengers <= 10);

    std::cout << "Initialization Test Passed!" << std::endl;
}

void testPopulationUpdate() {
    // Create a small 2x2 grid with certain initial population densities
    Grid grid(2, 2, 0.1, 0.02, 0.02, 0.01, 0.02, 0.05, 0.1, 10, 10, 10);

    // Store initial populations
    double initialPrey = grid.getPrey(0, 0);
    double initialPredators = grid.getPredators(0, 0);
    double initialScavengers = grid.getScavengers(0, 0);

    // Update the grid (this simulates the biological process)
    grid.update();

    // After updating, populations should change (though not drastically)
    double updatedPrey = grid.getPrey(0, 0);
    double updatedPredators = grid.getPredators(0, 0);
    double updatedScavengers = grid.getScavengers(0, 0);

    // Ensure the populations have changed (simple check, should be > initial values)
    assert(updatedPrey != initialPrey);
    assert(updatedPredators != initialPredators);
    assert(updatedScavengers != initialScavengers);

    std::cout << "Population Update Test Passed!" << std::endl;
}

int main() {
    // Run the tests
    testInitialization();
    testPopulationUpdate();

    std::cout << "All tests passed successfully!" << std::endl;
    return 0;
}
