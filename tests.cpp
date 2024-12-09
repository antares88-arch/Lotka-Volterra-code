#include <iostream>
#include <cassert>
#include "Ambiente.h"  

void testInizializzazione() {
    // Griglia 2x2; inserisco "a mano" i dati relativi alla simulazione **1
    Ambiente Ambiente(2, 2, 0.1, 0.02, 0.02, 0.01, 0.02, 0.05, 0.1, 10, 10, 10);

    // Popolazione iniziale nell'ambiente pari a zero
    double prede = Ambiente.getPrede(0, 0);
    double predatori = Ambiente.getPredatori(0, 0);
    double spazzini = Ambiente.getSpazzini(0, 0);

    // Il range accettato è tra 0 e il numero della popolazione da me inserito in **1
    assert(prede >= 0 && prede <= 10);
    assert(predatori >= 0 && predatori <= 10);
    assert(spazzini >= 0 && spazzini <= 10);

    std::cout << "Inizializzazione passata." << std::endl;
}

void testPopolazioneAggiorna() {
    
    Ambiente Ambiente(2, 2, 0.1, 0.02, 0.02, 0.01, 0.02, 0.05, 0.1, 10, 10, 10);

   
    double PredeIniziali = Ambiente.getPrede(0, 0);
    double PredatoriIniziali = Ambiente.getPredatori(0, 0);
    double SpazziniIniziali = Ambiente.getSpazzini(0, 0);

    
    Ambiente.aggiorna();

    
    double aggiornaPrede = Ambiente.getPrede(0, 0);
    double aggiornaPredatori = Ambiente.getPredatori(0, 0);
    double aggiornaSpazzini = Ambiente.getSpazzini(0, 0);

    //La popolazione, dopo l'aggiornamento (i.e. la simulazione dell'evoluzione dell'ambiente), deve cambiare
    assert(aggiornaPrede != PredeIniziali);
    assert(aggiornaPredatori != PredatoriIniziali);
    assert(aggiornaSpazzini != SpazziniIniziali);

    std::cout << "Aggiornamento della popolazione passato." << std::endl;
}

int main() {
  
    testInizializzazione();
    testPopolazioneAggiorna();

    std::cout << "Tutti i test hanno avuto esito positivo." << std::endl;
    return 0;
}
