#include <iostream>
#include "Zadanie.h"
#include "Problem.h"
#include "Rozwiazanie.h"
#include <chrono>


int main(int argc, char* argv[]) {
    if (argc < 2) {
        std::cerr << "Wywołanie: " << argv[0] << " <numer instancji>" << std::endl;
        return 1;
    }

    std::string nazwaPliku = "dane.txt";
    int nr = std::stoi(argv[1]);

    Problem test;
    Rozwiazanie wynik;
    test.wczytaj_dane(nazwaPliku, nr);
    wynik.wyswietl_menu();
    wynik.wybierz_metode(test);

    return 0;
}
