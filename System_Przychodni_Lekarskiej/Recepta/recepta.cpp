#include "recepta.h"

Recepta::Recepta(int id_recepty, int id_pacjenta, string data_wystawienia)
    : data_wystawienia(data_wystawienia), id_pacjenta(id_pacjenta), data_wystawienia(data_wystawienia) {}

void Recepta::dodajPozycja(string nazwa_leku, string dawkowanie) {
    pozycje.push_back(make_unique<PozycjaRecepty>(nazwa_leku, dawkowanie));
}

const vector<unique_ptr<PozycjaRecepty>>& Recepta::getPozycje() const {
    return pozycje;
}

int Recepta::getIdRecepty() const {
    return id_recepty;
}

int Recepta::getIdPacjenta() const {
    return id_pacjenta;
}