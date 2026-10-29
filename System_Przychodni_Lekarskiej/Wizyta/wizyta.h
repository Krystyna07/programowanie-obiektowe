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
    int id_wizyty;
    string data_wizyty;
    string status;
    shared_ptr<SlotCzasowy> slot;
    shared_ptr<Lekarz> lekarz;
    shared_ptr<Pacjent> pacjent;
    shared_ptr<Recepta> recepta;

public:
    Wizyta(
        int id_wizyty, 
        shared_ptr<Lekarz> lekarz, 
        shared_ptr<Pacjent> pacjent, 
        shared_ptr<SlotCzasowy> slot,
        string data_wizyty = "");

    void odwolajWizyte();
    void potwierdz();
    void przypiszRecepte(shared_ptr<Recepta> rec);

    int getIdWizyty() const;
    string getStatus() const;
    shared_ptr<Lekarz> getLekarz() const;
    shared_ptr<Pacjent> getPacjent() const;
    shared_ptr<SlotCzasowy> getSlot() const;
    shared_ptr<Recepta> getRecepta() const;
    string getDataWizyty() const;
};

#endif
