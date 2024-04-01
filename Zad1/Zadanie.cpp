#include "Zadanie.h"
#include <random>
#include <iostream>

Zadanie::Zadanie(int num, double pj, double rj, double qj){
    Zadanie::num=num;
    Zadanie::pj=pj;
    Zadanie::qj=qj;
    Zadanie::rj=rj;
}

Zadanie::Zadanie() {
    Zadanie::num=0;
    Zadanie::pj=0;
    Zadanie::qj=0;
    Zadanie::rj=0;
}

void Zadanie::generuj_wartosci() {
    std::random_device rd;
    std::mt19937 generator(rd());
    std::uniform_int_distribution<int> distribution(0, 10);
    std::uniform_int_distribution<int> distribution2(1, 5);
    this->rj=distribution(generator);
    this->qj=distribution2(generator);
    this->pj=distribution2(generator);
}

void Zadanie::wyswietl_zadanie() {
    std::cout<<"numer = "<<Zadanie::num<<std::endl<<"rj = "<<Zadanie::rj<<" qj = "<<Zadanie::qj<<" pj = "<<Zadanie::pj<<std::endl;

}

bool Zadanie::compare_rj(Zadanie z1, Zadanie z2) {
    return (z1.rj<z2.rj);
}

bool Zadanie::compare_qj(Zadanie z1, Zadanie z2) {
    return (z1.qj>z2.qj);
}

bool Zadanie::compare_qp(Zadanie z1, Zadanie z2) {
    return ((z1.qj+z1.pj)>(z2.qj+z2.pj));
}