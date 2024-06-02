#ifndef ZADANIE2_PROBLEM_H
#define ZADANIE2_PROBLEM_H
#include <vector>
#include "Zadanie.h"
#include <string>

class Problem {
private:
    int n; //liczba zadań
    int m; //liczba maszyn
    std::vector<Zadanie> dane;
public:
    Problem(int n, int m, const std::vector<Zadanie> &dane);
    Problem(int n, int m);
    Problem();

    int getN() const {return n;}
    void setN(int n) {
        Problem::n = n;
    }

    int getM() const {return m;}
    void setM(int m) {
        Problem::m = m;
    }

    const std::vector<Zadanie> &getDane() const {return dane;}
    void setDane(const std::vector<Zadanie> &dane) {
        Problem::dane = dane;
    }

    void wczytaj_dane(std::string &nazwaPliku, int nr_zad);

    void wypisz();

    std::vector<Zadanie> sortujZadaniaWedlugSumyCzasow();

    int rozmiar() const;

    void wstawZadanieNaPozycji(const Zadanie &zadanie, int pozycja);

    void wstawZadanie(const Zadanie &zadanie);
};


#endif
