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
    int getN()  {return n;}

    void setN(int n) {
        Problem::n = n;
    }

     std::vector<Zadanie> &getDane() {return dane;}

    void setDane( std::vector<Zadanie> &dane) {
        Problem::dane = dane;
    }

    Problem(int n, std::vector<Zadanie> &dane);
    Problem();
    void generuj_instancje();
    void wyswietl_problem();
    void wczytaj_dane(std::string& nazwaPliku);
    void sort_rj();
    void sort_qj();
    double licz_czas(std::vector<int> kolejnosc);

    void sort_qp();
};


#endif
