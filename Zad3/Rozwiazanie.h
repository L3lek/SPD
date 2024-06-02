#ifndef ZADANIE2_ROZWIAZANIE_H
#define ZADANIE2_ROZWIAZANIE_H
#include <vector>
#include <limits.h>
#include "Problem.h"

class Rozwiazanie {
private:
    std::vector<int> najlepszaKolejka; // Najlepsza kolejka zadań
    double najlepszyCmax; // Najlepsza wartość Cmax

public:
    const std::vector<int> &getNajlepszaKolejka() const {
        return najlepszaKolejka;
    }

    void setNajlepszaKolejka(const std::vector<int> &najlepszaKolejka) {
        Rozwiazanie::najlepszaKolejka = najlepszaKolejka;
    }

    double getNajlepszyCmax() const {
        return najlepszyCmax;
    }
    void setNajlepszyCmax(double najlepszyCmax) {
        Rozwiazanie::najlepszyCmax = najlepszyCmax;
    }

    void wyswietl_menu();

    void wybierz_metode(Problem &dane);

    void wyswietl();

    void wyswietl_kolejnosc();

    double obliczCmax(Problem &problem);

    void NEH(Problem &problem);

    void przeglad_zupelny(Problem &problem);

    void johnson(Problem &problem);
};


#endif