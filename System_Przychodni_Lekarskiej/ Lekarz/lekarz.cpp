#include "lekarz.h"
#include "wizyta.h"
#include "pacjent.h"
#include <iostream>

Lekarz::Lekarz(string imie, string nazwisko, int id, string specjalizacja, int id_lekarza, int stawka)
    : Osoba(imie, nazwisko, id), specjalizacja(specjalizacja), id_lekarza(id_lekarza), stawka_za_wizyte(stawka) {}

void Lekarz::dodajSlot(shared_ptr<SlotCzasowy> slot) {
    harmonogram.push_back(slot);
}

vector<SlotCzasowy*> Lekarz::getHarmonogramWolny() const {
    vector<SlotCzasowy*> wolne;
    for (const auto& slot : harmonogram) {
        if (slot && slot->czyWolny()) {
            wolne.push_back(slot.get());
        }     
    }
    return wolne;
}

shared_ptr<Recepta> Lekarz::wystawRecepte(Wizyta& wizyta, int id_recepty) {
    int id_pacjenta = 0;
    if (wizyta.getPacjent() != nullptr) {
        id_pacjenta = wizyta.getPacjent()->getIdPacjenta();
    }

    string data = wizyta.getDataWizyty();
    auto nowaRecepta = make_shared<Recepta>(id_recepty, id_pacjenta, data);

    cout << "Dr " << imie << " " << nazwisko 
         << " wystawil recepte nr " << id_recepty 
         << " (data: " << data << ") dla pacjenta ID: " << id_pacjenta << "\n";

    return nowaRecepta;
}


string Lekarz::getSpecjalizacja() const {
    return specjalizacja;
}

int Lekarz::getIdLekarza() const {
    return id_lekarza;
}

int Lekarz::getStawkaZaWizyte() const {
    return stawka_za_wizyte;
}

void Lekarz::wyswietlInformacje() const {
    cout << "ID Lekarza (PWZ): " << id_lekarza 
         << " | Dr " << imie << " " << nazwisko 
         << " | Specjalizacja: " << specjalizacja 
         << " | Stawka: " << stawka_za_wizyte << " PLN\n";
}
