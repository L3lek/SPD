#ifndef ZADANIE2_ZADANIE_H
#define ZADANIE2_ZADANIE_H
#include <string>

class Zadanie {
private:
    int num;
    double pj;

public:
    int getNum() const {return num;}

    void setNum(int num) {
        this->num = num;
    }

    double getPj() const {return pj;}

    void setPj(double pj) {
        Zadanie::pj = pj;
    }

    Zadanie(double num, int pj) : num(num), pj(pj) {}

    static bool compare(Zadanie z1, Zadanie z2);

    void zapisz_do_pliku(int n, const std::string &nazwa_pliku) const;

    double generuj_wartosc() const;

    Zadanie();
};


#endif
