#include "osoba.h"

Osoba::Osoba(string imie, string nazwisko, int id)
    : imie(imie), nazwisko(nazwisko), id(id) {}

string Osoba::getImie() const {
    return imie;
}

string Osoba::getNazwisko() const {
    return nazwisko;
}

string Osoba::getId() const {
    return id;
}
