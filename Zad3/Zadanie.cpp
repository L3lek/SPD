#include "Zadanie.h"
#include <fstream>
#include <iostream>
#include <random>

void Zadanie::wyswietl(){
    for(int i =0;i<tasks.size();i++){
        std::cout<<tasks[i]<<" ";
    }
}

Zadanie::Zadanie() {}

double Zadanie::pobierzSumeCzasow() const {
    double sumaCzasow = 0.0;
    for (size_t i = 0; i < tasks.size(); ++i) {
        sumaCzasow += tasks[i];
    }
    return sumaCzasow;
}

double Zadanie::pobierzCzasNaPozycji(int pozycja) const {
    if (pozycja >= 0 && pozycja < tasks.size()) {
        return tasks[pozycja];
    } else {
        return -1.0;
    }
}