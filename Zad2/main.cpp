#include <iostream>
#include "Zadanie.h"
#include "Problem.h"
#include "Rozwiazanie2p.h"


int main(){
//    Zadanie zadanie;
//    int liczba_danych = 6;
//    std::string nazwa_pliku = "dane.txt";
//    zadanie.zapisz_do_pliku(liczba_danych, nazwa_pliku);
    Problem test;
    std::string nazwaPliku = "dane1.txt";
    test.wczytaj_dane(nazwaPliku);
    Rozwiazanie2p wynik;
    wynik.wyswietl_menu();
    wynik.wybierz_metode(test);


    return 0;
}
