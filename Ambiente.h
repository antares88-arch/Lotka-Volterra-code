#ifndef griglia_H
#define griglia_H

#include <vector>
#include <random>

struct Cell {
    double prede;
    double predatori;
    double spazzini;  // Da letteratura, "scavengers". Questi possono essere identificati come qualsiasi animale necrofago (e.g. avvoltoi, iene)
};

//Ho nominato "ambiente" l'ambientazione della simulazione. Ci si immagini ad esempio un bosco (i.e. la griglia NxN nella sua totalità), diviso in zone (i.e. le celle).
//Ogni cella (da notare che NON vi è interazione TRA le celle ma SOLO all'INTERNO di ogni cella) è popolata da prede, predatori e spazzini.

//(std::vector<std::vector<Cell>>): Riga
//(std::vector<Cell>): ogni cella della riga

class Ambiente {
private:
    int larghezza_Griglia, altezza_griglia;
    double r, a, b, d, S_tasso_crescita, Cibo_spazzini, dt;
    std::vector<std::vector<Cell>> cells;

    // Generatore numeri casuali
    std::random_device rd;
    std::mt19937 gen; // Ho scelto questo perché dalla documentazione si evinceche sia consono per le applicazioni scientifiche

    void inizializzazioneGriglia(double DensPrede, double DensPredatori, double DensSpazzini);

public:

    Ambiente(int w, int h, double r, double a, double b, double d, double S_tasso_crescita, double Cibo_spazzini, double dt,
         double DensPrede, double DensPredatori, double DensSpazzini);

    // Ho aggiunto questi metodi solo per il test unitario
    double getPrede(int x, int y) const;
    double getPredatori(int x, int y) const;
    double getSpazzini(int x, int y) const;

    void aggiorna();

    void Applica_Disastro_Naturale();

    void Visualizza() const;
};

#endif
