#include "Rozwiazanie2p.h"
#include <iostream>
#include <vector>
#include <algorithm>

void Rozwiazanie2p::wyswietl_menu() {
    std::cout<<"Dostepne metody: "<<std::endl;
    std::cout<<"1 - LSA "<<std::endl;
    std::cout<<"2 - LPT "<<std::endl;
    std::cout<<"3 - PD dla dwoch procesorow "<<std::endl;
    std::cout<<"4 - Przeglad zupelny dla dwoch procesorow"<<std::endl;
    std::cout<<"5 - PTAS dla dwoch procesorow"<<std::endl;
    std::cout<<"6 - FPTAS dla dwoch procesorow"<<std::endl;
    std::cout<<"7 - Przeglad zupelny dla trzech procesorow "<<std::endl;
    std::cout<<"8 - PTAS dla trzech procesorow "<<std::endl;
    std::cout<<"9 - PD dla trzech procesorow "<<std::endl;
}

void Rozwiazanie2p::wyswietl(double kryterium) {
    std::cout<<"\nPosortowane rozwiazanie procesor 1: ";
    for (int i = 0; i < Rozwiazanie2p::procesor1.size(); ++i) {
        std::cout<<Rozwiazanie2p::procesor1[i]<<" ";
    }
    std::cout<<"\nPosortowane rozwiazanie procesor 2: ";
    for (int i = 0; i < Rozwiazanie2p::procesor2.size(); ++i) {
        std::cout<<Rozwiazanie2p::procesor2[i]<<" ";
    }

    std::cout<<std::endl<<"Wyliczone kryterium: "<<kryterium<<std::endl;
}

void Rozwiazanie2p::wybierz_metode(Problem &dane, int zmienna) {
    switch (zmienna) {
        case 1: {
            this->LSA(dane);
            this->wyswietl(this->licz_kryterium(dane));
            break;
        }
        case 2: {
            this->LPT(dane);
            this->wyswietl(this->licz_kryterium(dane));
            break;
        }
        case 3:{
            programowanie_dynamiczne(dane);
            this->wyswietl(this->licz_kryterium(dane));
            break;
        }
        case 4:{
            this->przeglad_zupelny(dane);
            this->wyswietl(this->licz_kryterium(dane));
            break;
        }
        case 5:{
            this->PTAS(dane, 0.8);
            this->wyswietl(this->licz_kryterium(dane));
            break;
        }
        case 6:{
            this->FPTAS(dane, 2);
            this->wyswietl(this->licz_kryterium(dane));
            break;
        }

        default:
            std::cout << "bledna opcja";
            break;
    }
}

double Rozwiazanie2p::licz_kryterium(Problem &dane) {
    double kryterium = std::max(dane.licz_cj((procesor1)),dane.licz_cj((procesor2)));
    return kryterium;
}

void Rozwiazanie2p::LPT(Problem &dane) {
    dane.sort();
    LSA(dane);
}

void Rozwiazanie2p::LSA(Problem &dane) {
    double czas1=0, czas2=0;
    for (int i = 0; i < dane.getN(); ++i) {
        Zadanie tmp = dane.getDane()[i];
        if (czas1 <= czas2) {
            this->procesor1.push_back(tmp.getNum());
            czas1 += tmp.getPj();
        } else {
            this->procesor2.push_back(tmp.getNum());
            czas2 += tmp.getPj();
        }
    }
}


void Rozwiazanie2p::generujBinarnie(Problem &dane, std::vector<int>& bity, int index) {
    std::vector<int> proc1, proc2;
    double C1 = 0, C2 = 0;
    double tmp;

    if (index == dane.getN()) {
        for (int i = 0; i < dane.getN(); ++i) {
            if (bity[i] == 1) {
                proc1.push_back(dane.getDane()[i].getNum());
                C1 += dane.getDane()[i].getPj();
            } else {
                proc2.push_back(dane.getDane()[i].getNum());
                C2 += dane.getDane()[i].getPj();
            }
        }
        tmp = std::abs(C2 - C1);
        if (tmp < roznica) {
            procesor1 = proc1;
            procesor2 = proc2;
            roznica = tmp;
        }

        return;
    }

    for (int i = 0; i <= 1; ++i) {
        bity[index] = i;
        generujBinarnie(dane, bity, index + 1);
    }
}

void Rozwiazanie2p::przeglad_zupelny(Problem &dane) {
    std::vector<int> bity(dane.getN());
    generujBinarnie(dane, bity, 1);
}

void Rozwiazanie2p::programowanie_dynamiczne(Problem &dane) {
    double C = 0;
    for (int i = 0; i < dane.getN(); i++) {
        C += dane.getDane()[i].getPj();
    }
    int n = dane.getN();
    int Kl = (C / 2) + 1;



    std::vector<std::vector<int>> T(n + 1, std::vector<int>(Kl, 0));

    for (int i = 0; i < n; ++i) {
        T[i][0] = 1;
    }

    for (int i = 0; i < n; i++) {
        Zadanie tmp = dane.getDane()[i];
        for (int k = 0; k < Kl; k++) {
            if (T[i][k] == 1) {
                if (T[i][tmp.getPj() + k] == 0) {
                    for (int j = i + 1; j <= n; j++) {
                        if((tmp.getPj() + k)<Kl){
                            T[j][tmp.getPj() + k] = 1;
                        }
                    }
                }
            }
        }
        if (T[i+1][Kl - 1] == 1) {
            break;
        }
    }

    int  koniec=1, znalenzione=0;
    while(Kl!=koniec){
        for(int i=0; i<n;++i){
            if(T[i][Kl -koniec] == 1){
                procesor1.push_back(i);
                koniec+=dane.getDane()[i-1].getPj();
                znalenzione=1;
                break;
            }
        }
        if(znalenzione==0){
            koniec++;
        }else{
            znalenzione=0;
        }
    }

    for(int i=1;i<=n;i++){
        if(std::find(procesor1.begin(), procesor1.end(), i) == procesor1.end()){
            procesor2.push_back(i);
        }
    }
}

void Rozwiazanie2p::PTAS(Problem &dane, double epsilon) {
    double C = 0;
    for (int i = 0; i < dane.getN(); i++) {
        C += dane.getDane()[i].getPj();
    }

    double Kl = C*epsilon/dane.getN();
    if(Kl>26){
        Kl=26;
    }

    std::vector<Zadanie> reduced_tasks;
    std::vector<Zadanie> remaining_tasks;

    for (int i = 0; i < dane.getN(); ++i) {
        if (dane.getDane()[i].getPj() <= Kl) {
            reduced_tasks.push_back(dane.getDane()[i]);
        } else {
            remaining_tasks.push_back(dane.getDane()[i]);
        }
    }
    Problem reduced;
    reduced.setDane(reduced_tasks);
    reduced.setN(reduced_tasks.size());

    Problem remaining;
    remaining.setDane(remaining_tasks);
    remaining.setN(remaining_tasks.size());
    reduced.sort();

    this->przeglad_zupelny(reduced);

   this->LSA(remaining);
}

void Rozwiazanie2p::FPTAS(Problem &dane, int epsilon) {
    Problem zmienione;
    zmienione.setN(dane.getN());
    zmienione=dane.nowe_dane(epsilon);
    this->programowanie_dynamiczne(zmienione);
}
