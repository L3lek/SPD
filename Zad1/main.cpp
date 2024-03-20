#include <iostream>
#include "Zadanie.h"
#include "Problem.h"
#include "Rozwiazanie.h"

int main() {
    Problem test;
    Rozwiazanie wynik;
    std::string nazwaPliku = "../dane3.txt";
    test.wczytaj_dane(nazwaPliku);
//    test.generuj_instancje(5);
    wynik.wyswietl_menu();
    wynik.wybierz_metode(test);
    wynik.wyswietl();
    return 0;
}
