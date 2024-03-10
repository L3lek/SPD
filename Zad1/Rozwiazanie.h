#ifndef ZADANIE1_ROZWIAZANIE_H
#define ZADANIE1_ROZWIAZANIE_H
#include "Zadanie.h"
#include <vector>
#include "Problem.h"

class Rozwiazanie {
private:
    double kryterium;
    std::vector<int> uszereg;
    double czas;
public:
    double getKryterium() const {return kryterium;}
    const std::vector<int> &getUszereg() const {return uszereg;}
    double getCzas() const {return czas;}

    void setKryterium(double kryterium) {
        Rozwiazanie::kryterium = kryterium;
    }

    void setUszereg(const std::vector<int> &uszereg) {
        Rozwiazanie::uszereg = uszereg;
    }

    void setCzas(double czas) {
        Rozwiazanie::czas = czas;
    }

    Rozwiazanie(double kryterium, const std::vector<int> &uszereg);
    Rozwiazanie();
    double oblicz_kryterium(Problem &dane, int i);
    void wyswietl_menu();
    void wyswietl();
    void wybierz_metode(Problem &dane);
    void pobierz_kolejnosc(Problem &dane);
    void przeglad_zupelny(Problem &);
    void generuj_permutacje(std::vector<int>& vec, int index, Problem &);

};


#endif
