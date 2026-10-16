#ifndef SLOT_CZASOWY_H
#define SLOT_CZASOWY_H

#include <string>
#include "lekarz.h"

using namespace std;

class SlotCzasowy {
private:
    string termin;
    bool czy_wolny;
    Lekarz* lekarz;

public:
    SlotCzasowy(
        string termin, 
        Lekarz* lekarz);

    string getTermin() const;
    bool isCzyWolny() const;
    Lekarz* getLekarz() const;

    void zajmi();
    void zwolnij();
    bool czyWolny() const;
};

#endif
