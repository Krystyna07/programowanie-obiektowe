#include "system_przychodni.h"
#include <iostream>
#include <vector>
#include <memory>
#include <string>

using namespace std;

void menuAdministratora(SystemPrzychodni& system) {
    int wybor = -1;
    while (wybor != 0) {
        cout << "\n--- ADMIN PANEL ---\n";
        cout << "1. Wyswietl liste wszystkich lekarzy i wolne terminy\n";
        cout << "2. Zarejestruj nowego pacjenta\n";
        cout << "3. Wyswietl liste wszystkich pacjentow\n";
        cout << "4. Wyswietl pelna historie wszystkich wizyt\n";
        cout << "0. Wroc do wyboru roli\n";
        cout << "Wybierz opcje: ";
        cin >> wybor;

        switch (wybor) {
            case 1: {
                cout << "\n--- LISTA LEKARZY ---\n";
                const auto& lekarze = system.getListaLekarzy();
                for (size_t i = 0; i < lekarze.size(); ++i) {
                    lekarze[i]->wyswietlInformacje();
                }
                break;
            }
            case 2: {
                string imie, nazwisko, pesel;
                int idOsoby, idPacjenta;
                cout << "\n--- REJESTRACJA PACJENTA ---\n";
                cout << "Imie: "; cin >> imie;
                cout << "Nazwisko: "; cin >> nazwisko;
                cout << "ID osoby: "; cin >> idOsoby;
                cout << "ID pacjenta: "; cin >> idPacjenta;
                cout << "PESEL: "; cin >> pesel;
                system.dodajPacjenta(make_shared<Pacjent>(imie, nazwisko, idOsoby, idPacjenta, pesel));
                cout << "[Sukces] Zarejestrowano pacjenta!\n";
                break;
            }
            case 3: {
                cout << "\n--- WSZYSCY PACJENCI ---\n";
                for (const auto& p : system.getListaPacjentow()) {
                    p->wyswietlInformacje();
                }
                break;
            }
            case 4: {
                cout << "\n--- WSZYSTKIE WIZYTY W SYSTEMIE ---\n";
                for (const auto& w : system.getListaWizyt()) {
                    cout << "ID: " << w->getIdWizyty() << " | Status: " << w->getStatus() 
                         << " | Data: " << w->getDataWizyty() 
                         << " | Lekarz PWZ: " << w->getLekarz()->getIdLekarza() 
                         << " | Pacjent PESEL: " << w->getPacjent()->getPesel() << "\n";
                }
                break;
            }
        }
    }
}

void menuLekarza(SystemPrzychodni& system) {
    string pwzStr;
    cout << "\nPodaj swoj numer PWZ (ID lekarza): ";
    cin >> pwzStr;

    shared_ptr<Lekarz> zalogowanyLekarz = nullptr;
    for (auto& l : system.getListaLekarzy()) {
        if (to_string(l->getIdLekarza()) == pwzStr) {
            zalogowanyLekarz = l;
            break;
        }
    }

    if (!zalogowanyLekarz) {
        cout << "[Blad] Nie znaleziono lekarza o takim numerze PWZ!\n";
        return;
    }

    int wybor = -1;
    while (wybor != 0) {
        cout << "\n--- PANEL LEKARZA: Dr " << zalogowanyLekarz->getImie() << " " << zalogowanyLekarz->getNazwisko() << " ---\n";
        cout << "1. Wyswietl moje wizyty\n";
        cout << "2. Wystaw recepte do wizyty (z dodaniem lekow)\n";
        cout << "3. Wyswietl moja statystyke i zarobki\n";
        cout << "0. Wroc do wyboru roli\n";
        cout << "Wybierz opcje: ";
        cin >> wybor;

        switch (wybor) {
            case 1: {
                cout << "\n--- MOJE WIZYTY ---\n";
                int count = 0;
                for (const auto& w : system.getListaWizyt()) {
                    if (w->getLekarz()->getIdLekarza() == zalogowanyLekarz->getIdLekarza()) {
                        cout << "ID Wizyty: " << w->getIdWizyty() << " | Data: " << w->getDataWizyty() 
                             << " | Status: " << w->getStatus() << " | Pacjent PESEL: " << w->getPacjent()->getPesel() << "\n";
                        count++;
                    }
                }
                if (count == 0) cout << "Brak wizyt.\n";
                break;
            }
            case 2: {
                int idWizyty;
                cout << "Podaj ID wizyty, dla ktorej chcesz wystawic recepte: ";
                cin >> idWizyty;

                vector<PozycjaRecepty> pozycje;
                char kontynuowac = 't';
                while (kontynuowac == 't' || kontynuowac == 'T') {
                    string lek, dawka;
                    cout << "Podaj nazwe leku: "; cin >> lek;
                    cout << "Podaj dawkowanie: "; cin >> dawka;
                    pozycje.push_back(PozycjaRecepty(lek, dawka));
                    cout << "Dodac kolejny lek? (t/n): ";
                    cin >> kontynuowac;
                }

                system.wystawRecepteInteraktywnie(idWizyty, pozycje);
                break;
            }
            case 3: {
                int liczbaWizyt = 0;
                for (const auto& w : system.getListaWizyt()) {
                    if (w->getLekarz()->getIdLekarza() == zalogowanyLekarz->getIdLekarza() && w->getStatus() != "Odwolana") {
                        liczbaWizyt++;
                    }
                }
                int zarobki = liczbaWizyt * zalogowanyLekarz->getStawkaZaWizyte();
                cout << "\n--- STATYSTYKA I ZAROBKI ---\n";
                cout << "Liczba zrealizowanych/zarezerwowanych wizyt: " << liczbaWizyt << "\n";
                cout << "Stawka za wizyte: " << zalogowanyLekarz->getStawkaZaWizyte() << " PLN\n";
                cout << "Laczny przychod/zarobek: " << zarobki << " PLN\n";
                break;
            }
        }
    }
}

void menuPacjenta(SystemPrzychodni& system) {
    string pesel;
    cout << "\nPodaj swoj numer PESEL: ";
    cin >> pesel;

    shared_ptr<Pacjent> zalogowanyPacjent = system.znajdzPacjentaPoPeselu(pesel);
    if (!zalogowanyPacjent) {
        cout << "[Blad] Nie znaleziono pacjenta o takim PESEL! Popros administratora o rejestracje.\n";
        return;
    }

    int wybor = -1;
    while (wybor != 0) {
        cout << "\n--- PANEL PACJENTA: " << zalogowanyPacjent->getImie() << " " << zalogowanyPacjent->getNazwisko() << " ---\n";
        cout << "1. Wyswietl dostepnych lekarzy i wolne terminy\n";
        cout << "2. Zarezerwuj wizyte\n";
        cout << "3. Wyswietl moje wizyty i recepty\n";
        cout << "4. Odwolaj swoja wizyte\n";
        cout << "0. Wroc do wyboru roli\n";
        cout << "Wybierz opcje: ";
        cin >> wybor;

        switch (wybor) {
            case 1: {
                system.wyswietlLekarzy();
                const auto& lekarze = system.getListaLekarzy();
                for (const auto& l : lekarze) {
                    auto wolne = l->getHarmonogramWolny();
                    cout << "Dr " << l->getNazwisko() << " (PWZ: " << l->getIdLekarza() << ") - Wolnych terminow: " << wolne.size() << "\n";
                    int limit = 0;
                    for (size_t j = 0; j < wolne.size() && limit < 3; ++j) {
                        cout << "   -> [" << j + 1 << "] " << wolne[j]->getTermin() << "\n";
                        limit++;
                    }
                }
                break;
            }
            case 2: {
                system.wyswietlLekarzy();
                string pwz;
                int idSlotu;
                cout << "Podaj PWZ lekarza: "; cin >> pwz;

                shared_ptr<Lekarz> wybranoLekarza = nullptr;
                for (auto& l : system.getListaLekarzy()) {
                    if (to_string(l->getIdLekarza()) == pwz) {
                        wybranoLekarza = l;
                        break;
                    }
                }

                if (!wybranoLekarza) {
                    cout << "[Blad] Nie znaleziono lekarza!\n";
                    break;
                }

                auto wolne = wybranoLekarza->getHarmonogramWolny();
                cout << "Dostepne sloty u lekarza:\n";
                for (size_t j = 0; j < wolne.size() && j < 15; ++j) {
                    cout << "ID Slotu [" << j + 1 << "] -> " << wolne[j]->getTermin() << "\n";
                }

                cout << "Wpisz numer (ID) slotu do rezerwacji: ";
                cin >> idSlotu;

                system.rezerwujWizyte(pesel, pwz, idSlotu);
                break;
            }
            case 3: {
                cout << "\n--- MOJE WIZYTY I RECEPTY ---\n";
                bool znaleziono = false;
                for (const auto& w : system.getListaWizyt()) {
                    if (w->getPacjent() && w->getPacjent()->getPesel() == pesel) {
                        znaleziono = true;
                        cout << "ID Wizyty: " << w->getIdWizyty() 
                             << " | Data: " << w->getDataWizyty() 
                             << " | Status: " << w->getStatus() 
                             << " | Lekarz PWZ: " << w->getLekarz()->getIdLekarza() << "\n";
                        
                        if (w->getRecepta()) {
                            cout << "   -> RECEPTA nr " << w->getRecepta()->getIdRecepty() << ":\n";
                            for (const auto& poz : w->getRecepta()->getPozycje()) {
                                cout << "      * Lek: " << poz->getNazwaLeku() << " | Dawkowanie: " << poz->getDawkowanie() << "\n";
                            }
                        } else {
                            cout << "   -> Brak recepty dla tej wizyty.\n";
                        }
                    }
                }
                if (!znaleziono) cout << "Brak zarejestrowanych wizyt.\n";
                break;
            }
            case 4: {
                int idWizyty;
                cout << "Podaj ID wizyty do odwolania: ";
                cin >> idWizyty;
                
                bool mojaWizyta = false;
                for (const auto& w : system.getListaWizyt()) {
                    if (w->getIdWizyty() == idWizyty && w->getPacjent() && w->getPacjent()->getPesel() == pesel) {
                        mojaWizyta = true;
                        break;
                    }
                }

                if (mojaWizyta) {
                    system.odwolajWizyte(idWizyty);
                } else {
                    cout << "[Blad] Nie mozesz odwolac cudzej wizyty lub taka wizyta nie istnieje!\n";
                }
                break;
            }
        }
    }
}

int main() {
    SystemPrzychodni system;

    if (!system.wczytajLekarzyZPliku("lekarze.txt")) {
        system.dodajLekarza(make_shared<Lekarz>("Jan", "Kowalski", 1, "Kardiolog", 1001, 150));
    }

    system.generujSlotyNaPolRoku();

    system.dodajPacjenta(make_shared<Pacjent>("Tomasz", "Lewandowski", 10, 1, "95010100111"));
    system.dodajPacjenta(make_shared<Pacjent>("Katarzyna", "Dabrowska", 11, 2, "96020200222"));

    int rola = -1;
    while (rola != 0) {
        cout << "\n=== WYBIERZ ROLE W SYSTEMIE ===\n";
        cout << "1. Administrator\n";
        cout << "2. Lekarz\n";
        cout << "3. Pacjent\n";
        cout << "0. Wyjscie\n";
        cout << "Wybierz role: ";
        cin >> rola;

        switch (rola) {
            case 1:
                menuAdministratora(system);
                break;
            case 2:
                menuLekarza(system);
                break;
            case 3:
                menuPacjenta(system);
                break;
            case 0:
                cout << "Zamykanie systemu. Do widzenia!\n";
                break;
            default:
                cout << "Nieznana opcja. Sprobuj ponownie.\n";
        }
    }

    return 0;
}
