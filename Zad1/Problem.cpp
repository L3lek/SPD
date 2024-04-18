#include <iostream>
#include <fstream>
#include <bits/stdc++.h>
#include "Problem.h"

Problem::Problem(int n, std::vector<Zadanie> &dane){
    Problem::n=n;
    Problem::dane=dane;
}
Problem::Problem(){
    std::vector<Zadanie> Dane;
    Problem::n=0;
    Problem::dane=Dane;
}
void Problem::generuj_instancje() {
    for (int i = 0; i < n; ++i) {
        Zadanie tmp;
        tmp.generuj_wartosci();
        tmp.setNum(i+1);
        this->dane.push_back(tmp);
    }
}

void Problem::wyswietl_problem() {
    for (int i = 0; i < Problem::dane.size(); ++i) {
        Problem::dane[i].wyswietl_zadanie();
    }
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
    for (int i = 1; i <= n; ++i) {
        double pj,rj,qj;
        plik >> rj >> pj >> qj;
        if (plik.fail()) {
            std::cerr << "Blad podczas wczytywania danych dla zadania " << i << std::endl;
            plik.close();
            return;
        }
        Zadanie tmp(i,pj,rj,qj);
        this->dane.push_back(tmp);
    }
    std::cout<<"Dane wczytane"<<std::endl;
    plik.close();
}

void Problem::sort_rj() {
std::sort(Problem::dane.begin(), Problem::dane.end(), Zadanie::compare_rj);
}

void Problem::sort_qj() {
    std::sort(Problem::dane.begin(), Problem::dane.end(), Zadanie::compare_qj);
}

void Problem::sort_qp() {
    std::sort(Problem::dane.begin(), Problem::dane.end(), Zadanie::compare_qp);
}

double Problem::licz_czas(std::vector<int> kolejnosc) {
    double czas_caly = 0;
    double cmax=0;
    for (int i = 0; i < this->getN(); ++i){
        Zadanie pom = this->dane[kolejnosc[i]-1];
        if(i==0){
            cmax=pom.getPj()+pom.getRj();
            czas_caly = cmax+pom.getQj();
        }else{
            czas_caly = std::max(std::max(cmax, pom.getRj()) + pom.getPj()+pom.getQj(), czas_caly);
            cmax=std::max(cmax, pom.getRj()) + pom.getPj();
        }
    }
    return czas_caly;
}




