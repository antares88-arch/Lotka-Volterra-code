#include "Grid.h"
#include <iostream>
int main() {
    int width, height, steps, disasterFrequency;
    double r, a, b, d, s_growth_rate, scavengerFood, dt, preyDensity, predatorDensity, scavengerDensity;

    std::cout << "Welcome to the Grid-Based Volterra-Lotka Simulator!\n";
    std::cout << "Enter grid width: ";
    std::cin >> width;
    std::cout << "Enter grid height: ";
    std::cin >> height;
    std::cout << "Enter prey growth rate (r): ";
    std::cin >> r;
    std::cout << "Enter predation rate (a): ";
    std::cin >> a;
    std::cout << "Enter predator reproduction rate (b): ";
    std::cin >> b;
    std::cout << "Enter predator natural death rate (d): ";
    std::cin >> d;
    std::cout << "Enter scavenger growth rate (s_growth_rate): ";
    std::cin >> s_growth_rate;
    std::cout << "Enter scavenger food source (scavengerFood): ";
    std::cin >> scavengerFood;
    std::cout << "Enter time step (dt): ";
    std::cin >> dt;
    std::cout << "Enter initial prey density: ";
    std::cin >> preyDensity;
    std::cout << "Enter initial predator density: ";
    std::cin >> predatorDensity;
    std::cout << "Enter initial scavenger density: ";
    std::cin >> scavengerDensity;
    std::cout << "Enter number of simulation steps: ";
    std::cin >> steps;
    std::cout << "Enter natural disaster frequency (0 for no disasters): ";
    std::cin >> disasterFrequency;

    Grid grid(width, height, r, a, b, d, s_growth_rate, scavengerFood, dt, preyDensity, predatorDensity, scavengerDensity);

    for (int step = 0; step < steps; ++step) {
        std::cout << "\nStep " << step + 1 << ":\n";
        grid.update();
        grid.display();

        if (disasterFrequency > 0 && (step + 1) % disasterFrequency == 0) {
            grid.applyNaturalDisaster();
        }
    }

    std::cout << "Simulation complete.\n";
    return 0;
}
