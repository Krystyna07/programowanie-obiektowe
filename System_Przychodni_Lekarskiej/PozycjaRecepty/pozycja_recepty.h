#ifndef POZYCJA_RECEPTY_H
#define POZYCJA_RECEPTY_H

#include <string>

using namespace std;

class PozycjaRecepty {
private:
    string nazwa_leku;
    string dawkowanie;

public:
    PozycjaRecepty(
        string nazwa_leku, 
        string dawkowanie);

    string getNazwaLeku() const;
    string getDawkowanie() const;
};

#endif
