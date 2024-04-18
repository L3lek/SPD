#include <iostream>
#include "Zadanie.h"
#include "Problem.h"
#include "Rozwiazanie.h"
#include <limits>

int main() {
    Problem test;
    Rozwiazanie wynik;
    std::string nazwaPliku = "../dane2.txt";
    test.wczytaj_dane(nazwaPliku);
    wynik.wyswietl_menu();
    wynik.wybierz_metode(test);
    wynik.wyswietl();
    return 0;
}
