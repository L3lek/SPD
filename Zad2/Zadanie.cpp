#include "Zadanie.h"
#include <fstream>
#include <iostream>
#include <random>
bool Zadanie::compare(Zadanie z1, Zadanie z2) {
    return (z1.pj >= z2.pj);
}

double Zadanie::generuj_wartosc() const {
    std::random_device rd;
    std::mt19937 generator(rd());
    std::uniform_int_distribution<int> distribution(1,20);
    double num = distribution(generator);
    return num;
}

void Zadanie::zapisz_do_pliku(int n, const std::string& nazwa_pliku) const {
    std::ofstream plik(nazwa_pliku, std::ios::app);
    if (plik.is_open()) {
        plik <<  n << "\n";
        for (int i = 0; i < n; ++i) {
            double num = this->generuj_wartosc();
            plik <<  num << "\n";
        }
        plik.close();
        std::cout << "Dane zapisane do pliku \"" << nazwa_pliku << "\".\n";
    } else {
        std::cerr << "Nie można otworzyć pliku do zapisu.\n";
    }
}

Zadanie::Zadanie() {

}
