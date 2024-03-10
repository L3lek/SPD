#include <iostream>
#include "Zadanie.h"
#include "Problem.h"
#include "Rozwiazanie.h"

int main() {
    Problem test;
    Rozwiazanie wynik;
    std::vector<int> tmp = {3,2,1};
    std::string nazwaPliku = "../1.txt";
    test.wczytaj_dane(nazwaPliku);
    // test.licz_czas(tmp);
    wynik.przeglad_zupelny(test);
//    test.generuj_instancje(5);
    // wynik.wyswietl_menu();
    // wynik.wybierz_metode(test);
    // wynik.wyswietl();
    return 0;
}
