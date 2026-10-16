#ifndef SYSTEM_PRZYCHODNI_H
#define SYSTEM_PRZYCHODNI_H

#include <vector>
#include <memory>
#include "lekarz.h"
#include "pacjent.h"
#include "wizyta.h"

using namespace std;

class SystemPrzychodni {
private:
    vector<unique_ptr<Lekarz>> wszyscy_lekarze;
    vector<unique_ptr<Pacjent>> wszyscy_pacjenci;
    vector<unique_ptr<Wizyta>> lista_wizyt;
    int next_wizyta_id = 1;

public:
    SystemPrzychodni() = default;

    void dodajLekarza(unique_ptr<Lekarz> lekarz); 
    void dodajPacjenta(unique_ptr<Pacjent> pacjent);

    Wizyta* zarezerwujWizyta(
        int id_pacjenta, 
        int id_lekarza, 
        SlotCzasowy* slot);
    bool odwolajWizyta(int id_wizyty);
    vector<SlotCzasowy*> wolnesloty(int id_lekarza) const;

    const vector<unique_ptr<Lekarz>>& getWszyscyLekarze() const;
    const vector<unique_ptr<Pacjent>>& getWszyscyPacjenci() const;
    const vector<unique_ptr<Wizyta>>& getListaWizyt() const;
};

#endif
