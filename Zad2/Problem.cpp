#include "Problem.h"
#include <string>
#include <iostream>
#include <fstream>
#include <bits/stdc++.h>
#include <algorithm>


Problem::Problem(int n, const std::vector<Zadanie> &dane){
    Problem::n=n;
    Problem::dane=dane;
}
Problem::Problem(int n) {
    std::vector<Zadanie> Dane(n);
    Problem::n=n;
    Problem::dane=Dane;
}
Problem::Problem(){
    std::vector<Zadanie> Dane;
    Problem::n=0;
    Problem::dane=Dane;
}

void Problem::wczytaj_dane(std::string& nazwaPliku) {
    std::ifstream plik(nazwaPliku);
    if (!plik.is_open()) {
        std::cerr << "Nie udalo sie otworzyc pliku." << std::endl;
        return;
    }

    plik >> this->n;

    if (plik.fail()) {
        std::cerr << "Blad podczas wczytywania wartosci n." << std::endl;
        plik.close();
        return;
    }
    for (int i = 0; i < n; ++i) {
        double pj;
        plik >> pj;
        if (plik.fail()) {
            std::cerr << "Blad podczas wczytywania danych dla zadania " << i + 1<< std::endl;
            plik.close();
            return;
        }
        Zadanie tmp(i+1,pj);
        this->dane.push_back(tmp);
    }
    std::cout<<"Dane wczytane"<<std::endl;
    plik.close();
}

void Problem::sort(){
    std::sort(Problem::dane.begin(), Problem::dane.end(), Zadanie::compare);
}

double Problem::licz_cj(std::vector<int> zbior) {
    int cj=0;
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < zbior.size(); ++j) {
            if(dane[i].getNum()==zbior[j])
                cj+=dane[i].getPj();
        }
    }
    return cj;
}

void Problem::wypisz(){
    for (int i = 0; i < n; ++i) {
        std::cout<<dane[i].getNum()<<std::endl;

    }
}
void Problem::wypisz_pj(){
    for (int i = 0; i < n; ++i) {
        std::cout<<dane[i].getPj()<<std::endl;

    }
}
Problem Problem::nowe_dane(double epsilon){
    Problem zmienione;
    zmienione.n= this->n;
    for (int i = 0; i < n; ++i) {
        Zadanie tmp;
        tmp.setNum(i+1);
        double num =this->dane[i].getPj()/epsilon;
        tmp.setPj(num);
        zmienione.dane.push_back(tmp);
    }
    return zmienione;
}


