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

    struct CompareRj {
        bool operator()(const Zadanie &a, const Zadanie &b) {
            return a.getRj() > b.getRj();
        }
    };

    struct CompareQj {
        bool operator()(const Zadanie &a, const Zadanie &b) {
            return a.getQj() < b.getQj();
        }
    };

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

    void przeglad_zupelny(Problem &dane);

    void generuj_permutacje(std::vector<int> &szereg, int index, Problem &dane);
    double Schrage(Problem &dane);

    int max_qj(std::vector<Zadanie> dane){
        int max=dane[0].getQj();
        int indeks =0;
        for (int i = 1; i < dane.size(); ++i) {
            max=std::max(dane[i].getQj(),dane[i-1].getQj());
            if(max==dane[i].getQj())
                indeks=i;
            else
                indeks=i-1;
        }
        return indeks;
    }

    double Schrage_pmtn(Problem &dane);

    void uporzadkuj_dane(Problem &dane);

    double Carlier(Problem &dane,double UB);
    int znajdz_b(std::vector<Zadanie>, double C_max);
    int znajdz_a(std::vector<Zadanie>, int b);
    int znajdz_c(std::vector<Zadanie>, int a, int b);



};


#endif
