#include "Grid.h"
#include <iostream>
#include <cmath>
#include <iomanip>

void Grid::initializeGrid(double preyDensity, double predatorDensity, double scavengerDensity) {
    std::uniform_real_distribution<> preyDist(0, preyDensity);
    std::uniform_real_distribution<> predatorDist(0, predatorDensity);
    std::uniform_real_distribution<> scavengerDist(0, scavengerDensity);

    for (auto& row : cells) {
        for (auto& cell : row) {
            cell.prey = preyDist(gen);
            cell.predators = predatorDist(gen);
            cell.scavengers = scavengerDist(gen);
        }
    }
}

Grid::Grid(int w, int h, double r, double a, double b, double d, double s_growth_rate, double scavengerFood, double dt,
           double preyDensity, double predatorDensity, double scavengerDensity)
    : width(w), height(h), r(r), a(a), b(b), d(d), s_growth_rate(s_growth_rate), scavengerFood(scavengerFood), dt(dt),
      cells(h, std::vector<Cell>(w)), gen(rd()) {
    initializeGrid(preyDensity, predatorDensity, scavengerDensity);
}

double Grid::getPrey(int x, int y) const {
    return cells[y][x].prey;
}

double Grid::getPredators(int x, int y) const {
    return cells[y][x].predators;
}

double Grid::getScavengers(int x, int y) const {
    return cells[y][x].scavengers;
}

// This function updates the population of each type in every grid cell using the Volterra-Lotka equations for prey and predators and adding scavenger growth based
// on available food (prey and predators).

void Grid::update() {
    for (auto& row : cells) {
        for (auto& cell : row) {
            // Compute changes based on Volterra-Lotka equations
            double dN = r * cell.prey - a * cell.prey * cell.predators;
            double dP = b * cell.prey * cell.predators - d * cell.predators;

            // Update populations
            cell.prey = std::abs(cell.prey + dN * dt);  // Ensure no negative values
            cell.predators = std::abs(cell.predators + dP * dt);  // Ensure no negative values

            // Scavenger updates
            double scavengerFood = cell.prey * 0.1 + cell.predators * 0.05;  // Scavengers feed on prey and predators
            double dS = s_growth_rate * scavengerFood;
            cell.scavengers = std::abs(cell.scavengers + dS * dt);  // Ensure no negative values
        }
    }
}
//This function randomly selects a grid cell and wipes out all populations there (prey, predators, and scavengers).
void Grid::applyNaturalDisaster() {
    std::uniform_int_distribution<> xDist(0, width - 1);
    std::uniform_int_distribution<> yDist(0, height - 1);

    int affectedX = xDist(gen);
    int affectedY = yDist(gen);

    // Wipe out populations in a random cell
    cells[affectedY][affectedX].prey = 0;
    cells[affectedY][affectedX].predators = 0;
    cells[affectedY][affectedX].scavengers = 0;

    std::cout << "Natural disaster at (" << affectedY << ", " << affectedX << ") wiped out all populations there.\n";
}
// This function prints the grid state for each cell and displays the total populations of each type (prey, predators, and scavengers).
//auto& row:

//The loop goes through each row in the cells vector.
//auto& automatically deduces the type of row (in this case, std::vector<Cell>&).
//The & means it accesses the row by reference, so it can modify the actual data in cells.
//auto& cell:

//The inner loop goes through each Cell in the current row.
//uto& deduces the type of cell (in this case, Cell&).
//Again, & means it accesses the cell by reference, allowing you to modify its prey and predators values.
//The use of auto& is convenient and reduces boilerplate code. Without auto, the same loop would look like this:

/*
Copia codice
for (std::vector<Cell>& row : cells) {
    for (Cell& cell : row) {
        // Operations on each cell
    }
}
While both are valid, auto& makes the code shorter and easier to read.*/
void Grid::display() const {
    std::cout << "Grid State (P=Prey, X=Predators, S=Scavengers, . = Balanced):\n";
    for (const auto& row : cells) {
        for (const auto& cell : row) {
            char symbol = '.';
            if (cell.prey > cell.predators && cell.prey > cell.scavengers) {
                symbol = 'P';  // Prey dominate
            } else if (cell.predators > cell.prey) {
                symbol = 'X';  // Predators dominate
            } else if (cell.scavengers > cell.prey && cell.scavengers > cell.predators) {
                symbol = 'S';  // Scavengers dominate
            }

            // Round population values and display integer counts
            std::cout << symbol << "("
                      << std::fixed << std::setprecision(0)  // Set precision to 0 for integers
                      << std::round(cell.prey) << ","
                      << std::round(cell.predators) << ","
                      << std::round(cell.scavengers) << ") ";
        }
        std::cout << '\n';
    }

    // Display total population counts after each step
    double totalPrey = 0, totalPredators = 0, totalScavengers = 0;
    for (const auto& row : cells) {
        for (const auto& cell : row) {
            totalPrey += cell.prey;
            totalPredators += cell.predators;
            totalScavengers += cell.scavengers;
        }
    }

    std::cout << "Total Prey: " << std::round(totalPrey) << ", Total Predators: "
              << std::round(totalPredators) << ", Total Scavengers: " << std::round(totalScavengers) << '\n';
}
