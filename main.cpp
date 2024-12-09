#include "Ambiente.h"
#include <iostream>
//NOTE  --Aggiorna == evolve per professore   --Ambiente == simulation per professore
int main() {
    int larghezza_Griglia, altezza_griglia, iterazioni, FreqDisastroNat;
    double r, a, b, d, S_tasso_crescita, Cibo_spazzini, dt, DensPrede, DensPredatori, DensSpazzini;

    std::cout << "Benvenuti! Effettueremo una simulazione basata sulle equazioni di Volterra-Lotka!" << std::endl << 
    "Si fa notare che tra parentesi verranno riportati dei prametri ottimali per la simulazione in esecuzione\n";
    std::cout << "Inserire la larghezza della griglia che simulerà l'ambiente della simulazione  (8-15): ";
    std::cin >> larghezza_Griglia;
    std::cout << "inserire l'altezza della griglia che simulerà l'ambiente della simulazione (8-15): ";
    std::cin >> altezza_griglia;
    std::cout << "Inserire il tasso di crescita delle prede (0.1-0.8): ";
    std::cin >> r;
    std::cout << "Inserire il tasso di crescita dei predatori (0.01-0.1): ";
    std::cin >> a;
    std::cout << "Inserire il tasso di riproduzione dei predatori (0.01-0.03): ";
    std::cin >> b;
    std::cout << "Inserire il tasso di mortalità dei predatori (d; 0.1-0.2): ";
    std::cin >> d;
    std::cout << "inserire il tasso di crescita degli spazzini (S_tasso_crescita; 0.1-0.15): ";
    std::cin >> S_tasso_crescita;
    std::cout << "inserire la quantità di cibo disponibile per gli spazzini (0.1-0.2): ";
    std::cin >> Cibo_spazzini;
    std::cout << "inserire il valore del singolo lasso temporale (0.01-0.1): ";
    std::cin >> dt;
    std::cout << "Inserire il numero iniziale delle prede presenti in ogni casella (15-30): ";
    std::cin >> DensPrede;
    std::cout << "Inserire il numero iniziale dei predatori presenti in ogni casella (4-7): ";
    std::cin >> DensPredatori;
    std::cout << "Inserire il numero iniziale degli spazzini presenti in ogni casella (1-3): ";
    std::cin >> DensSpazzini;
    std::cout << "inserire il numero di iterazioni (30-100): ";
    std::cin >> iterazioni;
    std::cout << "Inserire la frequenza dei disastri naturali (0 per alcun disastro): ";
    std::cin >> FreqDisastroNat;

    Ambiente Ambiente(larghezza_Griglia, altezza_griglia, r, a, b, d, S_tasso_crescita, Cibo_spazzini, dt, DensPrede, DensPredatori, DensSpazzini);

    for (int passo = 0; passo < iterazioni; ++passo) {
        std::cout << "\npasso " << passo + 1 << ":\n";
        Ambiente.aggiorna();
        Ambiente.Visualizza();

        if (FreqDisastroNat > 0 && (passo + 1) % FreqDisastroNat == 0) {
            Ambiente.Applica_Disastro_Naturale();
        }
    }

    std::cout << "Simulazione completa.\n";
    return 0;
}
