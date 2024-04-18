#ifndef ZADANIE2_ROZWIAZANIE2P_H
#define ZADANIE2_ROZWIAZANIE2P_H
#include <vector>
#include <limits.h>
#include "Problem.h"

class Rozwiazanie2p {
private:
    std::vector<int> procesor1;
    std::vector<int> procesor2;
    std::vector<int> procesor3;
    int roznica = INT_MAX;

public:
    const std::vector<int> &getProcesor1() const {return procesor1;}

    void setProcesor1(const std::vector<int> &procesor1) {
        Rozwiazanie2p::procesor1 = procesor1;
    }

    const std::vector<int> &getProcesor2() const {return procesor2;}

    void setProcesor2(const std::vector<int> &procesor2) {
        Rozwiazanie2p::procesor2 = procesor2;
    }

    double licz_kryterium(Problem &dane);

    void LPT(Problem &dane);;
    void LSA(Problem &dane);;

    void wyswietl_menu();

    void wybierz_metode(Problem &dane);

    void wyswietl(double kryterium);

    void generujBinarnie(Problem &dane, std::vector<int>& bits, int index);

    void przeglad_zupelny(Problem &dane);

    void programowanie_dynamiczne(Problem &dane);

    void PTAS(Problem &dane, double epsilon);

    void FPTAS(Problem &dane, double epsilon);

    void FPTAS(Problem &dane, int epsilon);

    void generujTrojkowo(Problem &dane, std::vector<int>& bity, int index);

    void przeglad_zupelny3p(Problem &dane);
};


#endif