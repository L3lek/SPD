#ifndef ZADANIE2_PROBLEM_H
#define ZADANIE2_PROBLEM_H
#include <vector>
#include "Zadanie.h"
#include <string>

class Problem {
private:
    int n;
    std::vector<Zadanie> dane;
public:
    Problem(int n, const std::vector<Zadanie> &dane);
    Problem(int n);
    Problem();

    int getN() const {return n;}

    void setN(int n) {
        Problem::n = n;
    }

    const std::vector<Zadanie> &getDane() const {return dane;}

    void setDane(const std::vector<Zadanie> &dane) {
        Problem::dane = dane;
    }

    void wczytaj_dane(std::string &nazwaPliku);

    void sort();

    double licz_cj(std::vector<int> zbior);
    void wypisz();

    Problem nowe_dane(double epsilon);

    void wypisz_pj();
};


#endif
