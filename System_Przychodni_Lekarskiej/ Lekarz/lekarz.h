#ifndef LEKARZ_H
#define LEKARZ_H

#include "osoba.h"
#include <string>
#include <vector>
#include <memory>
#include "wizyta.h"
#include "recepta.h"
#include "slot_czasowy.h"

using namespace std;

class Lekarz : public Osoba {
private:
    string specjalizacja;
    int id_lekarza;
    int stawka_za_wizyte;
    vector<unique_ptr<SlotCzasowy>> harmonogram;

public:
    Lekarz(
        string imie,
        string nazwisko,
        int id,
        string specjalizacja, 
        int id_lekarza, 
        int stawka);

    void przeprowadzicWizyta(Wizyta& wizyta);
    unique_ptr<Recepta> wystawRecepta(Wizyta& wizyta, int id_recepty);

    void dodajSlot(string termin);

    string getSpecjalizacja() const;
    int getIdLekarza() const;
    int getStawkaZaWizyte() const;
    vector<SlotCzasowy*> getHarmonogramWolny() const;

    void wyswietlInformacje() const override; // override
};

#endif
