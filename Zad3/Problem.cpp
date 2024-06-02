#include "Problem.h"
#include <string>
#include <iostream>
#include <fstream>
#include <bits/stdc++.h>
#include <algorithm>


Problem::Problem(int n, int m, const std::vector<Zadanie> &dane){
    Problem::n=n;
    Problem::m=m;
    Problem::dane=dane;
}
Problem::Problem(int n, int m) {
    std::vector<Zadanie> Dane(n);
    Problem::n=n;
    Problem::m=m;
    Problem::dane=Dane;
}
Problem::Problem(){
    std::vector<Zadanie> Dane;
    Problem::n=0;
    Problem::m=0;
    Problem::dane=Dane;
}

void Problem::wczytaj_dane(std::string& nazwaPliku, int nr) {
        std::ifstream plik(nazwaPliku);
        if (!plik.is_open()) {
            std::cerr << "Nie udalo sie otworzyc pliku." << std::endl;
            return;
        }

        int iloscInstancji;
        plik >> iloscInstancji;

        if (nr < 0 || nr >= iloscInstancji) {
            std::cerr << "Nieprawidłowy numer instancji." << std::endl;
            exit(1);
        }

        nr=nr-1;
        for (int i = 0; i < iloscInstancji; ++i) {
            int m_temp, n_temp;
            plik >> n_temp >> m_temp;

            if (i != nr) {
                for (int l = 0; l < m_temp; ++l) {
                    for (int j = 0; j < n_temp; ++j) {
                        int index, value;
                        plik >> index >> value;
                    }
                }
            } else {
                this->m = m_temp;
                this->n = n_temp;
                for (int j = 0; j < n_temp; ++j) {
                    std::vector<double> tasks;
                    for (int k = 0; k < m_temp; ++k) {
                        int index, value;
                        plik >> index >> value;
                        tasks.push_back(value);
                    }
                    dane.push_back(Zadanie(j, tasks));
                }
                break;
            }
        }
        plik.close();
}


void Problem::wypisz(){
    std::cout<<"n: "<<this->getN() <<" m: "<<this->getM()<<std::endl;
    for (int i = 0; i < n; ++i) {
        std::cout<<i<<std::endl;
        dane[i].wyswietl();
        std::cout<<std::endl;
    }
}

std::vector<Zadanie> Problem::sortujZadaniaWedlugSumyCzasow(){
    std::vector<Zadanie> posortowane(dane.begin(), dane.end());
    std::sort(posortowane.begin(), posortowane.end(), [](const Zadanie& a, const Zadanie& b) {
        return a.pobierzSumeCzasow() > b.pobierzSumeCzasow();
    });
    return posortowane;
}

void Problem::wstawZadanie(const Zadanie& zadanie) {
    dane.push_back(zadanie);
}

void Problem::wstawZadanieNaPozycji(const Zadanie& zadanie, int pozycja) {
    dane.insert(dane.begin() + pozycja, zadanie);
}

int Problem::rozmiar() const {
    return dane.size();
}

