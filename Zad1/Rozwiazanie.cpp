#include "Rozwiazanie.h"
#include <cmath>
#include <iostream>

Rozwiazanie::Rozwiazanie(double kryterium, const std::vector<int> &uszereg){
    Rozwiazanie::kryterium=kryterium;
    Rozwiazanie::uszereg=uszereg;
    Rozwiazanie::czas=1000000;
}
Rozwiazanie::Rozwiazanie(){
    std::vector<int> szereg;
    Rozwiazanie::kryterium=0;
    Rozwiazanie::uszereg=szereg;
    Rozwiazanie::czas=1000000;
}

double Rozwiazanie::oblicz_kryterium(Problem &dane, int i) {
    if (i==0){
        Zadanie tmp=dane.getDane()[i];
        return tmp.getRj()+tmp.getPj()+tmp.getQj();
    }else{
        double pop = oblicz_kryterium(dane,i-1);
        Zadanie tmp=dane.getDane()[i];
        return std::max(pop-dane.getDane()[i-1].getQj(),tmp.getRj())+tmp.getPj()+tmp.getQj();
    }
}

void Rozwiazanie::wyswietl_menu() {
    std::cout<<"Dostepne metody: "<<std::endl;
    std::cout<<"1 - sortowanie po rj "<<std::endl;
    std::cout<<"2 - sortowanie po qj "<<std::endl;
}

void Rozwiazanie::wyswietl() {
    std::cout<<"Posortowane rozwiazanie: ";
    for (int i = 0; i < Rozwiazanie::uszereg.size(); ++i) {
        std::cout<<Rozwiazanie::uszereg[i]<<" ";
    }
    std::cout<<std::endl<<"Wyliczone kryterium: "<<Rozwiazanie::kryterium<<std::endl;
}

void Rozwiazanie::pobierz_kolejnosc(Problem &dane) {
    for (int i = 0; i < dane.getDane().size(); ++i) {
        Zadanie tmp=dane.getDane()[i];
        this->uszereg.push_back(tmp.getNum());
    }
}

void Rozwiazanie::wybierz_metode(Problem &dane) {
    std::cout<<"wybierz metode ";
    int zmienna=100;
    std::cin>>zmienna;
        switch (zmienna) {
            case 1:
                dane.sort_rj();
                break;
            case 2:
                dane.sort_qj();
                break;
            default:
                std::cout << "blędna opcja";
                break;
        }

    std::cout<<"Posortowano"<<std::endl;
    double kryt=this->oblicz_kryterium(dane,dane.getDane().size()-1);
    this->kryterium=kryt;
    std::cout<<"Obliczono kryterium"<<std::endl;
    this->pobierz_kolejnosc(dane);
    std::cout<<"Przekopiowano"<<std::endl;
}

void Rozwiazanie::generuj_permutacje(std::vector<int>& vec, int index, Problem &problem) {
    if (index == vec.size() - 1) {
        // Reached the end of the vector, call your function
        double porownywana = problem.licz_czas(vec);
        if(porownywana<czas){
            this->czas=porownywana;
            this->uszereg=vec;
        } 
        return;
    }

    for (int i = index; i < vec.size(); ++i) {
        std::swap(vec[index], vec[i]);

        generuj_permutacje(vec, index + 1, problem);

        std::swap(vec[index], vec[i]);
    }
}

void Rozwiazanie::przeglad_zupelny(Problem &problem) {
    std::vector<int> indices;
    for (int i = 1; i <= problem.getN(); ++i) {
        indices.push_back(i);
    }

    generuj_permutacje(indices, 0,problem);

    std::cout <<"Optymalnym rozwiązaniem jest ułożenie zadań w kolejności: "<< std::endl;
    for(int i =0; i< this->uszereg.size();i++){
    std::cout << this->uszereg[i]<< " ";
    }
    std::cout << "o czasie: "<< this->czas << std::endl;
}



