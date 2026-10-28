#include "pacjent.h"
#include "wizyta.h"
#include <iostream>
#include <algorithm>

Pacjent::Pacjent(string imie, string nazwisko, int id, int id_pacjenta)
    : Osoba(imie, nazwisko, id), id_pacjenta(id_pacjenta) {}

void Pacjent::dodajWizyta(Wizyta* wizyta) {
    if (wizyta != nullptr) {
        wizyty.push_back(wizyta);
    }
}

void Pacjent::usunWizyta(Wizyta* wizyta) {
    auto it = std::remove(wizyty.begin(), wizyty.end(), wizyta);
    if (it != wizyty.end()) {
        wizyty.erase(it, wizyty.end());
    }
}

int Pacjent::getIdPacjenta() const {
    return id_pacjenta;
}

const vector<Wizyta*>& Pacjent::getWizyty() const {
    return wizyty;
}

void Pacjent::wyswietlInformacje() const {
    cout << "ID Osoby: " << id
    << "ID Pacjenta: " << id_pacjenta
    << "Imie:" << imie 
    <<"Nazwisko" << nazwisko 
    << "Zaplanowane wizyty: " << wizyty.size() << endl;
}

