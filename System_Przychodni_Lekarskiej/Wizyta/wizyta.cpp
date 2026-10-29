#include "wizyta.h"
#include "slot_czasowy.h"
#include "recepta.h"

Wizyta::Wizyta(int id, shared_ptr<Lekarz> l, shared_ptr<Pacjent> p, shared_ptr<SlotCzasowy> s, string data)
    : id_wizyty(id), lekarz(l), pacjent(p), slot(s), data_wizyty(data), status("Zarezerwowana"), recepta(nullptr) {}

void Wizyta::odwolajWizyte() {
    status = "Odwolana";
    if (slot != nullptr) {
        slot->zwolnij(); 
    }
}

void Wizyta::potwierdz() {
    status = "Potwierdzona";
}

void Wizyta::przypiszRecepte(shared_ptr<Recepta> rec) {
    recepta = rec;
    status = "Zakonczona"; 
}

int Wizyta::getIdWizyty() const {
    return id_wizyty;
}

string Wizyta::getStatus() const {
    return status;
}

shared_ptr<Lekarz> Wizyta::getLekarz() const {
    return lekarz;
}

shared_ptr<Pacjent> Wizyta::getPacjent() const {
    return pacjent;
}

shared_ptr<SlotCzasowy> Wizyta::getSlot() const {
    return slot;
}

shared_ptr<Recepta> Wizyta::getRecepta() const {
    return recepta;
}

string Wizyta::getDataWizyty() const {
    return data_wizyty;
}
