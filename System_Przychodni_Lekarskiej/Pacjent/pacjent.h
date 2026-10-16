#ifndef RECEPTA_H
#define RECEPTA_H

#include <string>
#include <vector>
#include <memory>
#include "pozycja_recepty.h"

using namespace std;

class Recepta {
private:
    string data_wystawienia;
    vector<unique_ptr<PozycjaRecepty>> pozycje;
    int id_recepty;
    int id_pacjenta;

public:
    Recepta(
        int id_recepty,
        int id_pacjenta, 
        string data_wystawienia);

    void dodajPozycja(string nazwa_leku, string dawkowanie);
    int getIdRecepty() const;
    int getIdPacjenta() const;
    const vector<unique_ptr<PozycjaRecepty>>& getPozycje() const;
};

#endif
