#ifndef WIZYTA_H
#define WIZYTA_H

#include <string>
#include <memory>
#include "slot_czasowy.h"
#include "recepta.h"

using namespace std;

class Lekarz;
class Pacjent;

class Wizyta {
private:
    string data_wizyty;
    SlotCzasowy* slot;
    int id_wizyty;
    string status;
    Lekarz* lekarz;
    Pacjent* pacjent;
    unique_ptr<Recepta> recepta;
public:
    Wizyta(
        int id_wizyty, 
        string data_wizyty, 
        SlotCzasowy* slot, 
        Lekarz* lekarz, 
        Pacjent* pacjent);

    void odwolaj();
    void potwierdz();
    void przypiszRecepte(unique_ptr<Recepta> rec);

    int getIdWizyty() const;
    string getStatus() const;
    Lekarz* getLekarz() const;
    Pacjent* getPacjent() const;
    SlotCzasowy* getSlot() const;
    Recepta* getRecepta() const;
};

#endif
