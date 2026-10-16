#ifndef OSOBA_H
#define OSOBA_H

#include <string>

using namespace std;

class Osoba {
protected:
    string imie;
    string nazwisko;
    int id;

public:
    Osoba(
        string imie, 
        string nazwisko, 
        int id);
    virtual ~Osoba() = default;   // destruktor wirtualny

    string getImie() const;
    string getNazwisko() const;
    int getId() const;

    virtual void wyswietlInformacje() const = 0; 
};

#endif
