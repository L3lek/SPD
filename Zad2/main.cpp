#include <iostream>
#include "Zadanie.h"
#include "Problem.h"
#include "Rozwiazanie2p.h"
#include "Rozwiazanie3p.h"
#include <chrono>


int main(){
    int zmienna;
//    Zadanie zadanie;
//    int liczba_danych = 12;
//    std::string nazwa_pliku = "dane10.txt";
//    zadanie.zapisz_do_pliku(liczba_danych, nazwa_pliku);
    Problem test;
    std::string nazwaPliku = "dane4.txt";
    test.wczytaj_dane(nazwaPliku);
    Rozwiazanie2p wynik;
    Rozwiazanie3p wynik3;
    wynik.wyswietl_menu();
    std::cout<<"wybierz metode    ";
    std::cin>>zmienna;
    if(zmienna<7){
        wynik.wybierz_metode(test,zmienna);
    }else{
        wynik3.wybierz_metode(test,zmienna);
    }

    return 0;
}
