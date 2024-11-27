#ifndef GRID_H
#define GRID_H

#include <vector>
#include <random>

// Struct to hold population data for each grid cell
//he struct Cell is used to represent the state of each "cell" in the grid. Each cell contains:

//prey: The population of prey in that cell.
//predators: The population of predators in that cell.
//By using a struct, we bundle these two variables together because they are always logically linked: a cell in the grid has both prey and predator populations. This simplifies the code and makes it easier to manage and understand.
struct Cell {
    double prey;
    double predators;
    double scavengers;  // Scavenger population
};

// Grid class to manage the simulation
//his is a two-dimensional vector, which represents the grid in the simulation.

//Outer vector (std::vector<std::vector<Cell>>): Represents rows of the grid.
//Inner vector (std::vector<Cell>): Represents the cells in each row.
//So, cells is essentially a grid of Cell objects. Here's how it works:

//Each element in the outer vector is a row of the grid.
//Each element in the inner vector is a single cell in that row.
//For example:

//If the grid has 3 rows and 4 columns, cells will contain 3 outer vectors (rows), each containing 4 Cell objects (columns).
class Grid {
private:
    int width, height;
    double r, a, b, d, s_growth_rate, scavengerFood, dt;
    std::vector<std::vector<Cell>> cells;

    // Random number generator
    std::random_device rd;
    std::mt19937 gen;

    void initializeGrid(double preyDensity, double predatorDensity, double scavengerDensity);

public:
    // Constructor
    Grid(int w, int h, double r, double a, double b, double d, double s_growth_rate, double scavengerFood, double dt,
         double preyDensity, double predatorDensity, double scavengerDensity);

    // Getter methods to access population data at specific grid locations
    double getPrey(int x, int y) const;
    double getPredators(int x, int y) const;
    double getScavengers(int x, int y) const;

    // Update populations based on the Volterra-Lotka equations
    void update();

    // Apply a natural disaster (wipes out populations in a random grid cell)
    void applyNaturalDisaster();

    // Display grid state
    void display() const;
};

#endif // GRID_H
