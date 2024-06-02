#ifndef ZADANIE2_ROZWIAZANIE3P_H
#define ZADANIE2_ROZWIAZANIE3P_H
#include <vector>
#include <limits.h>
#include "Problem.h"

class Rozwiazanie3p {
private:
    std::vector<int> procesor1;
    std::vector<int> procesor2;
    std::vector<int> procesor3;
    int roznica = INT_MAX;

public:
    const std::vector<int> &getProcesor1() const {return procesor1;}

    void setProcesor1(const std::vector<int> &procesor1) {
        Rozwiazanie3p::procesor1 = procesor1;
    }

    const std::vector<int> &getProcesor2() const {return procesor2;}

    void setProcesor2(const std::vector<int> &procesor2) {
        Rozwiazanie3p::procesor2 = procesor2;
    }

    const std::vector<int> &getProcesor3() const {return procesor3;}

    void setProcesor3(const std::vector<int> &procesor1) {
        Rozwiazanie3p::procesor3 = procesor3;
    }

    void generujTrojkowo(Problem &dane, std::vector<int>& bity, int index);

    void przeglad_zupelny3p(Problem &dane);

    void wyswietl(Problem &dane);

    void wybierz_metode(Problem &dane, int zmienna);

    double licz_kryterium(Problem &dane);

    void LSA(Problem &dane);

    void LPT(Problem &dane);

    void PTAS(Problem &dane, double epsilon);

    void programowanie_dynamiczne3p(Problem &dane);

    void displayArray(const std::vector<std::vector<int>>& T);
};


#endif