#ifndef SLOT_CZASOWY_H
#define SLOT_CZASOWY_H

#include <string>

using namespace std;

class Lekarz;

class SlotCzasowy {
private:
    string termin;
    bool czy_wolny;
    Lekarz* lekarz;

public:
 
    SlotCzasowy(string termin, Lekarz* lekarz = nullptr);

    string getTermin() const;
    Lekarz* getLekarz() const;

    void zajmi();
    void zwolnij();
    bool czyWolny() const;
};

#endif
