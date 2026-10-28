#include "lekarz.h"
#include "pacjent.h"
#include <iostream>

Lekarz::Lekarz(string imie, string nazwisko, int id, string specjalizacja, int id_lekarza, int stawka)
    : Osoba(imie, nazwisko, id), specjalizacja(specjalizacja), id_lekarza(id_lekarza), stawka_za_wizyte(stawka) {}

void Lekarz::dodajSlot(string termin) {
    harmonogram.push_back(make_unique<SlotCzasowy>(termin));
}

vector<SlotCzasowy*> Lekarz::getHarmonogramWolny() const{
    vector<SlotCzasowy*> wolne;
    for (const auto& slot : harmonogram) {
        if (slot && slot->czyWolny()) {
            wolne.push_back(slot.get());
        }     
    }
    return wolne;
}

void Lekarz::przeprowadzicWizyta(Wizyta& wizyta) {
    cout << "DR" << imie << "" << nazwisko 
    << "poprowadzi wizyta" << endl;
    wizyta.potwierdz();
}

unique_ptr<Recepta> Lekarz::wystawRecepta(Wizyta& wizyta, int id_recepty) {
int id_pacjenta = 0;
if (wizyta.getPacjent != nullptr) {
    id_pacjenta = wizyta.getPacjent()->getIdPacjenta();
}

string data = wizyta.getDataWizyty();
auto nowaRecepta = make_unique<Recepta>(id_recepty, id_pacjenta, data);

cout << "DR" << imie << "" << nazwisko 
    << " wystawil recepte nr " << id_recepty
    << " (data: " << data << ") dla pacjenta o ID: " << id_pacjenta << endl;

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
    cout << " ID Lekarza: " << id_lekarza 
         << "DR:" << imie << " " << nazwisko 
         << "Specjalizacja: " << specjalizacja 
         << "Stawka za wizyte: " << stawka_za_wizyte << " PLN" 
         << "Wszystkich slotow: " << harmonogram.size() 
         << " wolnych: " << getHarmonogramWolny().size() << "" << endl;

}