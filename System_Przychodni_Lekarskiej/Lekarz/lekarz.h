#ifndef LEKARZ_H
#define LEKARZ_H

#include "osoba.h"
#include <string>
#include <vector>
#include <memory>
#include "slot_czasowy.h"
#include "recepta.h"
#include "wizyta.h"

using namespace std;

class Wizyta; 

class Lekarz : public Osoba {
private:
    string specjalizacja;
    int id_lekarza; // PWZ
    int stawka_za_wizyte;
    vector<shared_ptr<SlotCzasowy>> harmonogram;

public:
    Lekarz(string imie, string nazwisko, int id, string specjalizacja, int id_lekarza, int stawka);

    void dodajSlot(shared_ptr<SlotCzasowy> slot);
    string getSpecjalizacja() const;
    int getIdLekarza() const;
    int getStawkaZaWizyte() const;
    vector<SlotCzasowy*> getHarmonogramWolny() const;

    shared_ptr<Recepta> wystawRecepte(Wizyta& wizyta, int id_recepty);

    void wyswietlInformacje() const override;
};

#endif
