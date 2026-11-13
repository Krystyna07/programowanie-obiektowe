#include "system_przychodni.h"

#include <iostream>
#include <fstream>
#include <sstream>
#include <chrono>
#include <ctime>
#include <iomanip>

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

bool SystemPrzychodni::wczytajLekarzyZPliku(const string& nazwaPliku) {
    ifstream plik(nazwaPliku);
    if (!plik.is_open()) {
        return false;
    }

    string linia;
    while (getline(plik, linia)) {
        if (linia.empty()) continue;
        stringstream ss(linia);
        string imie, nazwisko, specjalizacja;
        int idOsoby, idLekarza, stawka;
        char srednik;

        getline(ss, imie, ';');
        getline(ss, nazwisko, ';');
        ss >> idOsoby >> srednik;
        getline(ss, specjalizacja, ';');
        ss >> idLekarza >> srednik >> stawka;

        auto lekarz = make_shared<Lekarz>(imie, nazwisko, idOsoby, specjalizacja, idLekarza, stawka);
        dodajLekarza(lekarz);
    }
    plik.close();
    return true;
}

void SystemPrzychodni::generujSlotyNaPolRoku() {
    auto now = chrono::system_clock::now();
    time_t currentTime = chrono::system_clock::to_time_t(now);
    tm* localTime = localtime(&currentTime);

    int dniNaprzod = 180; 
    tm startDay = *localTime;

    for (int i = 0; i < dniNaprzod; ++i) {
        tm daySlot = startDay;
        daySlot.tm_mday += i;
        mktime(&daySlot); 

        if (daySlot.tm_wday == 0 || daySlot.tm_wday == 6) {
            continue;
        }

        int godziny[] = {9, 11, 14, 16};
        for (int godzina : godziny) {
            daySlot.tm_hour = godzina;
            daySlot.tm_min = 0;
            daySlot.tm_sec = 0;

            char buffer[80];
            strftime(buffer, sizeof(buffer), "%Y-%m-%d %H:%M", &daySlot);
            string terminStr(buffer);

            for (auto& lekarz : listaLekarzy) {
                auto slot = make_shared<SlotCzasowy>(terminStr, lekarz.get());
                katalogSlotow.push_back(slot);
                lekarz->dodajSlot(slot);
            }
        }
    }
}

shared_ptr<Pacjent> SystemPrzychodni::znajdzPacjentaPoPeselu(const string& pesel) {
    for (auto& p : listaPacjentow) {
        if (p->getPesel() == pesel) {
            return p;
        }
    }
    return nullptr;
}

void SystemPrzychodni::wyswietlLekarzy() const {
    cout << "[System] Dostępni lekarze:\n";
    for (size_t i = 0; i < listaLekarzy.size(); ++i) {
        cout << "  " << i + 1 << ". Dr " << listaLekarzy[i]->getImie() 
                  << " " << listaLekarzy[i]->getNazwisko() 
                  << " (Specjalizacja: " << listaLekarzy[i]->getSpecjalizacja() 
                  << ", PWZ: " << listaLekarzy[i]->getIdLekarza()
                  << ", Stawka: " << listaLekarzy[i]->getStawkaZaWizyte() << " PLN)\n";
    }
}

shared_ptr<Wizyta> SystemPrzychodni::rezerwujWizyte(const string& peselPacjenta, const string& pwzLekarza, int indeksSlotu) {
    shared_ptr<Pacjent> znalezionyPacjent = znajdzPacjentaPoPeselu(peselPacjenta);

    shared_ptr<Lekarz> znalezionyLekarz = nullptr;
    for (auto& l : listaLekarzy) {
        if (to_string(l->getIdLekarza()) == pwzLekarza) {
            znalezionyLekarz = l;
            break;
        }
    }

    if (!znalezionyPacjent || !znalezionyLekarz) {
        cout << "[Blad] Nie znaleziono pacjenta o takim PESEL lub lekarza o takim PWZ!\n";
        return nullptr;
    }

    auto wolneSloty = znalezionyLekarz->getHarmonogramWolny();
    if (indeksSlotu < 1 || indeksSlotu > static_cast<int>(wolneSloty.size())) {
        cout << "[Blad] Nieprawidłowy numer slotu!\n";
        return nullptr;
    }

    SlotCzasowy* wybranySlotPtr = wolneSloty[indeksSlotu - 1];

    shared_ptr<SlotCzasowy> znalezionySlot = nullptr;
    for (auto& s : katalogSlotow) {
        if (s->getTermin() == wybranySlotPtr->getTermin() && s->getLekarz() == wybranySlotPtr->getLekarz()) {
            znalezionySlot = s;
            break;
        }
    }

    if (!znalezionySlot || !znalezionySlot->czyWolny()) {
        cout << "[Blad] Wybrany slot jest już zajety lub niedostepny!\n";
        return nullptr;
    }

    znalezionySlot->zajmi();
    wybranySlotPtr->zajmi();

    int noweIdWizyty = static_cast<int>(listaWizyt.size()) + 1;
    auto nowaWizyta = make_shared<Wizyta>(noweIdWizyty, znalezionyLekarz, znalezionyPacjent, znalezionySlot, znalezionySlot->getTermin());

    znalezionyPacjent->dodajWizyta(nowaWizyta.get());
    listaWizyt.push_back(nowaWizyta);

    cout << "[Sukces] Zarezerwowano wizyte ID: " << noweIdWizyty 
              << " dla pacjenta PESEL: " << peselPacjenta 
              << " na " << znalezionySlot->getTermin() << "\n";

    return nowaWizyta;
}

void SystemPrzychodni::wystawRecepteInteraktywnie(int idWizyty, const vector<PozycjaRecepty>& pozycje) {
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

    if (!docelowaWizyta->getLekarz()) {
        cout << "[Blad] Ta wizyta nie ma przypisanego lekarza!\n";
        return;
    }

    int idRecepty = 100 + idWizyty;
    
    auto nowaRecepta = docelowaWizyta->getLekarz()->wystawRecepte(*docelowaWizyta, idRecepty);

    for (const auto& poz : pozycje) {
        nowaRecepta->dodajPozycja(poz.getNazwaLeku(), poz.getDawkowanie());
    }

    docelowaWizyta->przypiszRecepte(nowaRecepta);
    
    cout << "[Sukces] Pomyslnie wystawiono recepte nr " << idRecepty << " dla wizyty ID: " << idWizyty << " z " << pozycje.size() << " lekami.\n";
}





void SystemPrzychodni::odwolajWizyte(int idWizyty) {
    for (auto& w : listaWizyt) {
        if (w->getIdWizyty() == idWizyty) {
            w->odwolajWizyte();
            if (w->getPacjent() != nullptr) {
                w->getPacjent()->usunWizyta(w.get());
            }
            cout << "[Sukces] Odwolano wizyte ID: " << idWizyty << " (slot zostal zwolniony).\n";
            return;
        }
    }
    cout << "[Blad] Nie znaleziono wizyty o ID: " << idWizyty << " do odwolania.\n";
}

const vector<shared_ptr<Lekarz>>& SystemPrzychodni::getListaLekarzy() const { return listaLekarzy; }
const vector<shared_ptr<Pacjent>>& SystemPrzychodni::getListaPacjentow() const { return listaPacjentow; }
const vector<shared_ptr<Wizyta>>& SystemPrzychodni::getListaWizyt() const { return listaWizyt; }
