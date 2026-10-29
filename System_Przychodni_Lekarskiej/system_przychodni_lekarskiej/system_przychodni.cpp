#include "system_przychodni.h"
#include <iostream>

using namespace std;

void SystemPrzychodni::dodajPacjenta(shared_ptr<Pacjent> pacjent) {
    listaPacjentow.push_back(pacjent);
}

void SystemPrzychodni::dodajLekarza(shared_ptr<Lekarz> lekarz) {
    listaLekarzy.push_back(lekarz);
}

void SystemPrzychodni::dodajSlot(shared_ptr<SlotCzasowy> slot) {
    katalogSlotow.push_back(slot);
}

void SystemPrzychodni::wyswietlLekarzy() const {
    cout << "[System] Dostępni lekarze:\n";
    for (size_t i = 0; i < listaLekarzy.size(); ++i) {
            cout << "  " << i + 1 << ". Dr " << listaLekarzy[i]->getImie() 
                  << " " << listaLekarzy[i]->getNazwisko() 
                  << " (Specjalizacja: " << listaLekarzy[i]->getSpecjalizacja() 
                  << ", PWZ: " << listaLekarzy[i]->getIdLekarza() << ")\n";
    }
}

shared_ptr<Wizyta> SystemPrzychodni::rezerwujWizyte(const string& peselPacjenta, const string& pwzLekarza, int idSlotu) {
    shared_ptr<Pacjent> znalezionyPacjent = nullptr;
    for (auto& p : listaPacjentow) {
        if (p->getPesel() == peselPacjenta) {
            znalezionyPacjent = p;
            break;
        }
    }

    shared_ptr<Lekarz> znalezionyLekarz = nullptr;
    for (auto& l : listaLekarzy) {
        if (to_string(l->getIdLekarza()) == pwzLekarza) {
            znalezionyLekarz = l;
            break;
        }
    }

    shared_ptr<SlotCzasowy> znalezionySlot = nullptr;
    for (auto& s : katalogSlotow) {
        if (s.get() != nullptr) {
            znalezionySlot = s;
            break;
        }
    }

    
    if (!znalezionyPacjent || !znalezionyLekarz || !znalezionySlot) {
        cout << "[Blad] Nie znaleziono pacjenta, lekarza lub slotu!\n";
        return nullptr;
    }

    if (!znalezionySlot->czyWolny()) {
        cout << "[Blad] Wybrany slot jest już zajęty!\n";
        return nullptr;
    }

    znalezionySlot->zajmi();

    int noweIdWizyty = static_cast<int>(listaWizyt.size()) + 1;
    auto nowaWizyta = make_shared<Wizyta>(noweIdWizyty, znalezionyLekarz, znalezionyPacjent, znalezionySlot);

    listaWizyt.push_back(nowaWizyta);

    cout << "[Sukces] Zarezerwowano wizytę ID: " << noweIdWizyty 
              << " dla pacjenta PESEL: " << peselPacjenta << "\n";

    return nowaWizyta;
}

void SystemPrzychodni::wystawRecepte(int idWizyty, const vector<PozycjaRecepty>& pozycje) {
    shared_ptr<Wizyta> docelowaWizyta = nullptr;
    for (auto& w : listaWizyt) {
        if (w->getIdWizyty() == idWizyty) {
            docelowaWizyta = w;
            break;
        }
    }

    if (!docelowaWizyta) {
        cout << "[Blad] Nie znaleziono wizyty o ID: " << idWizyty << "\n";
        return;
    }

    cout << "[Sukces] Wystawiono receptę dla wizyty ID: " << idWizyty << "\n";
}

void SystemPrzychodni::odwolajWizyte(int idWizyty) {
    for (auto& w : listaWizyt) {
        if (w->getIdWizyty() == idWizyty) {
            if (w->getSlot() != nullptr) {
                w->getSlot()->zwolnij();
            }
           cout << "[Sukces] Odwołano wizytę ID: " << idWizyty << " (slot został zwolniony).\n";
            return;
        }
    }
    cout << "[Blad] Nie znaleziono wizyty o ID: " << idWizyty << " do odwołania.\n";
}

const vector<shared_ptr<Lekarz>>& SystemPrzychodni::getListaLekarzy() const {
    return listaLekarzy;
}

const vector<shared_ptr<Pacjent>>& SystemPrzychodni::getListaPacjentow() const {
    return listaPacjentow;
}

const vector<shared_ptr<Wizyta>>& SystemPrzychodni::getListaWizyt() const {
    return listaWizyt;
}
