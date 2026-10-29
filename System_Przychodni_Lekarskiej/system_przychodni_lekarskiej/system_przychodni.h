#ifndef SYSTEM_PRZYCHODNI_H
#define SYSTEM_PRZYCHODNI_H

#include <vector>
#include <memory>
#include <string>
#include "lekarz.h"
#include "pacjent.h"
#include "wizyta.h"
#include "slot_czasowy.h"
#include "pozycja_recepty.h"
#include "recepta.h"

using namespace std;

class SystemPrzychodni {
private:
    vector<shared_ptr<Lekarz>> listaLekarzy;
    vector<shared_ptr<Pacjent>> listaPacjentow;
    vector<shared_ptr<SlotCzasowy>> katalogSlotow;
    vector<shared_ptr<Wizyta>> listaWizyt;

public:
    SystemPrzychodni() = default;

    void dodajPacjenta(shared_ptr<Pacjent> pacjent);
    void dodajLekarza(shared_ptr<Lekarz> lekarz);
    void dodajSlot(shared_ptr<SlotCzasowy> slot);

    void wyswietlLekarzy() const;

    shared_ptr<Wizyta> rezerwujWizyte(const string& peselPacjenta, const string& pwzLekarza, int idSlotu);
    void wystawRecepte(int idWizyty, const vector<PozycjaRecepty>& pozycje);
    void odwolajWizyte(int idWizyty);

    const vector<shared_ptr<Lekarz>>& getListaLekarzy() const;
    const vector<shared_ptr<Pacjent>>& getListaPacjentow() const;
    const vector<shared_ptr<Wizyta>>& getListaWizyt() const;
};

#endif
