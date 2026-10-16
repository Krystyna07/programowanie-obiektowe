#ifndef PACJENT_H
#define PACJENT_H

#include "osoba.h"
#include <vector>
#include <string>

using namespace std;

class Wizyta;

class Pacjent : public Osoba {
private:
    int id_pacjenta;
    vector<Wizyta*> wizyty;

public:
    Pacjent(
        string imie, 
        string nazwisko, 
        int id, 
        int id_pacjenta);

    void dodajWizyta(Wizyta* wizyta);
    void usunWizyta(Wizyta* wizyta);

    int getIdPacjenta() const;
    const vector<Wizyta*>& getWizyty() const;

    void wyswietlInformacje() const override;
};

#endif
