#include "system_przychodni.h"
#include <iostream>
#include <vector>
#include <memory>
#include <string>

using namespace std;

int main() {
    SystemPrzychodni system;

    cout << "START SYSTEMU PRZYCHODNI LEKARSKIEJ\n\n";

    system.dodajLekarza(make_shared<Lekarz>("Jan", "Kowalski", 1, "Kardiolog", 1001, 120));
    system.dodajLekarza(make_shared<Lekarz>("Maria", "Wiśniewska", 2, "Neurolog", 1002, 150));
    system.dodajLekarza(make_shared<Lekarz>("Piotr", "Zieliński", 3, "Pediatra", 1003, 100));

    system.dodajPacjenta(make_shared<Pacjent>("Tomasz", "Lewandowski", 10, 1, "95010100111"));
    system.dodajPacjenta(make_shared<Pacjent>("Katarzyna", "Dąbrowska", 11, 2, "96020200222"));
    system.dodajPacjenta(make_shared<Pacjent>("Michał", "Zając", 12, 3, "97030300333"));

    system.dodajSlot(make_shared<SlotCzasowy>("2026-10-10 09:00"));
    system.dodajSlot(make_shared<SlotCzasowy>("2026-10-10 10:00"));
    system.dodajSlot(make_shared<SlotCzasowy>("2026-10-10 11:00"));

    system.wyswietlLekarzy();
    cout << "\n";

    cout << "--- LISTA PACJENTÓW W SYSTEMIE ---\n";
    for (const auto& p : system.getListaPacjentow()) {
        p->wyswietlInformacje();
    }
    cout << "\n";

    cout << "--- SCENARIUSZ 1: Rezerwacja wizyty i wystawienie recepty ---\n";
    string peselKasi = "96020200222";
    string pwzMarii = "1002";
    int idSlotu1 = 1;

    auto wizyta1 = system.rezerwujWizyte(peselKasi, pwzMarii, idSlotu1);

    if (wizyta1 != nullptr) {
            vector<PozycjaRecepty> leki = {
            PozycjaRecepty("Magne B6", "2x dziennie"),
            PozycjaRecepty("Ibuprom", "W razie bólu")
        };
        system.wystawRecepte(wizyta1->getIdWizyty(), leki);
    }
    cout << "\n";

    cout << "--- SCENARIUSZ 2: Rezerwacja kolejnej wizyty ---\n";
    string peselTomka = "95010100111";
    string pwzPiotra = "1003";
    int idSlotu2 = 2;

    auto wizyta2 = system.rezerwujWizyte(peselTomka, pwzPiotra, idSlotu2);
    cout << "\n";

    cout << "--- AKTUALNA HISTORIA WSZYSTKICH WIZYT ---\n";
    for (const auto& w : system.getListaWizyt()) {
        cout << "ID Wizyty: " << w->getIdWizyty() 
                  << " | Status: " << w->getStatus() 
                  << " | Data: " << w->getDataWizyty() << "\n";
    }
    cout << "\n";

    cout << "--- SCENARIUSZ 3: Odwołanie pierwszej wizyty ---\n";
    if (wizyta1 != nullptr) {
        system.odwolajWizyte(wizyta1->getIdWizyty());
    }
    cout << "\n";

    cout << "--- STAN WIZYT PO ODWOŁANIU ---\n";
    for (const auto& w : system.getListaWizyt()) {
        cout << "ID Wizyty: " << w->getIdWizyty() 
                  << " | Status: " << w->getStatus() << "\n";
    }

    cout << "\n=== KONIEC PROGRAMU ===\n";
    return 0;
}
