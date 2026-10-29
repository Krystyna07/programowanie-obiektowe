#include "slot_czasowy.h"

SlotCzasowy::SlotCzasowy(string termin, Lekarz* lekarz)
    : termin(termin), czy_wolny(true), lekarz(lekarz) {}

string SlotCzasowy::getTermin() const {
    return termin;
}

Lekarz* SlotCzasowy::getLekarz() const {
    return lekarz;
}

void SlotCzasowy::zajmi() {
    czy_wolny = false;
}

void SlotCzasowy::zwolnij() {
    czy_wolny = true;
}

bool SlotCzasowy::czyWolny() const {
    return czy_wolny;
}
