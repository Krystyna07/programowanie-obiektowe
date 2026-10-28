#include "pozycja_recepty.h"

PozycjaRecepty::PozycjaRecepty(string nazwa_leku, string dawkowanie) 
    : nazwa_leku(nazwa_leku), dawkowanie(dawkowanie) {}

string PozycjaRecepty::getNazwaLeku() const {
    return nazwa_leku;
}

string PozycjaRecepty::getDawkowanie() const {
    return dawkowanie;
}