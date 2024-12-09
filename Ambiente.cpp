#include "Ambiente.h"
#include <iostream>
#include <cmath>
#include <iomanip>

void Ambiente::inizializzazioneGriglia(double DensPrede, double DensPredatori, double DensSpazzini) {
    std::uniform_real_distribution<> predeDist(0, DensPrede);
    std::uniform_real_distribution<> predatorDist(0, DensPredatori);
    std::uniform_real_distribution<> scavengerDist(0, DensSpazzini);

    for (auto& riga : cells) {
        for (auto& cell : riga) {
            cell.prede = predeDist(gen);
            cell.predatori = predatorDist(gen);
            cell.spazzini = scavengerDist(gen);
        }
    }
}

Ambiente::Ambiente(int w, int h, double r, double a, double b, double d, double S_tasso_crescita, double Cibo_spazzini, double dt,
           double DensPrede, double DensPredatori, double DensSpazzini)
    : larghezza_Griglia(w), altezza_griglia(h), r(r), a(a), b(b), d(d), S_tasso_crescita(S_tasso_crescita), Cibo_spazzini(Cibo_spazzini), dt(dt),
      cells(h, std::vector<Cell>(w)), gen(rd()) {
    inizializzazioneGriglia(DensPrede, DensPredatori, DensSpazzini);
}

double Ambiente::getPrede(int x, int y) const {
    return cells[y][x].prede;
}

double Ambiente::getPredatori(int x, int y) const {
    return cells[y][x].predatori;
}

double Ambiente::getSpazzini(int x, int y) const {
    return cells[y][x].spazzini;
}

// La seguente funzione aggiorna la popolazione di ogni tipo in ciascuna cella dell'ambiente (griglia NxN) creato; ciò si basa sulle equazioni di Volterra-Lotka.

void Ambiente::aggiorna() {
    for (auto& riga : cells) {
        for (auto& cell : riga) {
            //Volterra-Lotka 
            double dN = r * cell.prede - a * cell.prede * cell.predatori;
            double dP = b * cell.prede * cell.predatori - d * cell.predatori;

            // Aggiorno la popolazione
            cell.prede = std::abs(cell.prede + dN * dt);  // Aassicuro il valore assoluto
            cell.predatori = std::abs(cell.predatori + dP * dt);  

            // Aggiorno anche gli spazzini
            double Cibo_spazzini = cell.prede * 0.1 + cell.predatori * 0.05;  // cibo disponibile per gli spazzini correlato alla presenza delle prede e dei predatori
            double dS = S_tasso_crescita * Cibo_spazzini;
            cell.spazzini = std::abs(cell.spazzini + dS * dt);  
        }
    }
}
//Seleziono randomicamente un disastro naturale che spazza via tutte le popolazioni da una cella dell'ambiente (prede, predatori e spazzini).
void Ambiente::Applica_Disastro_Naturale() {
    std::uniform_int_distribution<> xDist(0, larghezza_Griglia - 1);
    std::uniform_int_distribution<> yDist(0, altezza_griglia - 1);

    int DannoX = xDist(gen);
    int DannoY = yDist(gen);


    cells[DannoY][DannoX].prede = 0;
    cells[DannoY][DannoX].predatori = 0;
    cells[DannoY][DannoX].spazzini = 0;

    std::cout << "Un disastro naturale nella zona (" << DannoY+1 << "," << DannoX+1 << ") spazza via tutta la popolazione.\n";
}



void Ambiente::Visualizza() const {
    std::cout << "Stato dell'ambiente  (P=prede, X=predatori, S=spazzini, . = Bilanciato):\n";
    for (const auto& riga : cells) { //seleziono una riga
        for (const auto& cell : riga) { //Attraverso ogni riga e lavoro su tutte le celle di tale riga
            char simbolo = '.';
            if (cell.prede > cell.predatori && cell.prede > cell.spazzini) {
                simbolo = 'P';  // Dominano le prede
            } else if (cell.predatori > cell.prede) {
                simbolo = 'X';  // Dominano i predatori
            } else if (cell.spazzini > cell.prede && cell.spazzini > cell.predatori) {
                simbolo = 'S';  // Dominano gli spazzini
            }

            
            std::cout << simbolo << "("
                      << std::fixed << std::setprecision(0)  
                      << std::round(cell.prede) << ","
                      << std::round(cell.predatori) << ","
                      << std::round(cell.spazzini) << ") ";
        }
        std::cout << '\n';
    }

    // Visualizzazione popolazione totale ad ogni iterazione
    double totalprede = 0, totalpredatori = 0, totalspazzini = 0;
    for (const auto& riga : cells) {
        for (const auto& cell : riga) {
            totalprede += cell.prede;
            totalpredatori += cell.predatori;
            totalspazzini += cell.spazzini;
        }
    }

    std::cout << "Totale delle prede: " << std::round(totalprede) << ", Totale dei predatori: "
              << std::round(totalpredatori) << ", Totale degli spazzini: " << std::round(totalspazzini) << '\n';
}
