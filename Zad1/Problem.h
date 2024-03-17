#ifndef ZADANIE1_PROBLEM_H
#define ZADANIE1_PROBLEM_H
#include <vector>
#include <string>

#include "Zadanie.h"


class Problem {
private:
    int n;
    std::vector<Zadanie> dane;
public:
    int getN() const {return n;}

    void setN(int n) {
        Problem::n = n;
    }

    const std::vector<Zadanie> &getDane() const {return dane;}

    void setDane(const std::vector<Zadanie> &dane) {
        Problem::dane = dane;
    }

    Problem(int n, const std::vector<Zadanie> &dane);
    Problem();
    void generuj_instancje(int rozmiar);
    void wyswietl_problem();
    void wczytaj_dane(std::string& nazwaPliku);
    void sort_rj();
    void sort_qj();
};


#endif
