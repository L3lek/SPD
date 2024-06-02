#include "Rozwiazanie3p.h"
#include <iostream>
#include <vector>
#include <algorithm>
#include <chrono>

void Rozwiazanie3p::generujTrojkowo(Problem &dane, std::vector<int>& bity, int index) {
    std::vector<int> proc1, proc2, proc3;
    double C1=0, C2=0, C3=0;
    double tmp, tmp2, tmp3;

    if (index == dane.getN()) {
        for (int i = 0; i < dane.getN(); ++i) {
            if(bity[i]==0){
                proc1.push_back(dane.getDane()[i].getNum());
                C1 += dane.getDane()[i].getPj();
            } else if(bity[i]==1) {
                proc2.push_back(dane.getDane()[i].getNum());
                C2 += dane.getDane()[i].getPj();
            }else{
                proc3.push_back(dane.getDane()[i].getNum());
                C3 += dane.getDane()[i].getPj();
            }
        }

        tmp = std::abs(C2 - C1);
        tmp2 = std::abs(C3 - C1);
        tmp3 = std::abs(C3 - C2);

        if (tmp < roznica && tmp2 < roznica && tmp3 < roznica) {
            procesor1 = proc1;
            procesor2 = proc2;
            procesor3 = proc3;
            roznica = std::max({tmp, tmp2, tmp3});
        }
        return;
    }

    for (int i = 0; i <= 2; ++i) {
        bity[index] = i;
        generujTrojkowo(dane, bity, index + 1);
    }
}

void Rozwiazanie3p::przeglad_zupelny3p(Problem &dane) {
    std::vector<int> bity(dane.getN());
    generujTrojkowo(dane, bity, 0);
}

void Rozwiazanie3p::wyswietl(Problem &dane) {
    // std::cout<<"\nRozwiazanie procesor 1: ";
    // for (int i = 0; i < Rozwiazanie3p::procesor1.size(); ++i) {
    //     std::cout<<Rozwiazanie3p::procesor1[i]<<" ";
    // }
    std::cout<<std::endl<<"Czas P1: "<<dane.licz_cj((procesor1))<<std::endl;

    // std::cout<<"\nRozwiazanie procesor 2: ";
    // for (int i = 0; i < Rozwiazanie3p::procesor2.size(); ++i) {
    //     std::cout<<Rozwiazanie3p::procesor2[i]<<" ";
    // }
    std::cout<<std::endl<<"Czas P2: "<<dane.licz_cj((procesor2))<<std::endl;

    // std::cout<<"\nRozwiazanie procesor 3: ";
    // for (int i = 0; i < Rozwiazanie3p::procesor3.size(); ++i) {
    //     std::cout<<Rozwiazanie3p::procesor3[i]<<" ";
    // }
    std::cout<<std::endl<<"Czas P3: "<<dane.licz_cj((procesor3))<<std::endl;
}

void Rozwiazanie3p::wybierz_metode(Problem &dane, int zmienna) {
    switch (zmienna) {
        case 7:{
            auto start = std::chrono::high_resolution_clock::now();
            this->przeglad_zupelny3p(dane);
            this->wyswietl(dane);
            auto end = std::chrono::high_resolution_clock::now();
            auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();
            std::cout << "Czas wykonania: " << duration << " ms" << std::endl;
            break;
        }case 8:{
            auto start = std::chrono::high_resolution_clock::now();
            this->PTAS(dane,0.66);
            this->wyswietl(dane);
            auto end = std::chrono::high_resolution_clock::now();
            auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();
            std::cout << "Czas wykonania: " << duration << " ms" << std::endl;
            break;
        }
        case 9:{
            auto start = std::chrono::high_resolution_clock::now();
            this->programowanie_dynamiczne3p(dane);
            this->wyswietl(dane);
            auto end = std::chrono::high_resolution_clock::now();
            auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();
            std::cout << "Czas wykonania: " << duration << " ms" << std::endl;
            break;
        }
        case 10:{
            auto start = std::chrono::high_resolution_clock::now();
            this->LSA(dane);
            this->wyswietl(dane);
            auto end = std::chrono::high_resolution_clock::now();
            auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();
            std::cout << "Czas wykonania: " << duration << " ms" << std::endl;
            break;
        }
        case 11:{
            auto start = std::chrono::high_resolution_clock::now();
            this->LPT(dane);
            this->wyswietl(dane);
            auto end = std::chrono::high_resolution_clock::now();
            auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();
            std::cout << "Czas wykonania: " << duration << " ms" << std::endl;
            break;
        }
        default:
            std::cout << "bledna opcja";
            break;
    }
}

double Rozwiazanie3p::licz_kryterium(Problem &dane) {
    double kryterium = std::max(dane.licz_cj((procesor1)),dane.licz_cj((procesor2)));
    kryterium=std::max(kryterium,dane.licz_cj(procesor3));
    return kryterium;
}

void Rozwiazanie3p::LSA(Problem &dane) {
    double czas1=0, czas2=0, czas3=0;
    for (int i = 0; i < dane.getN(); ++i) {
        Zadanie tmp = dane.getDane()[i];
        if (czas1 <= czas2) {
            this->procesor1.push_back(tmp.getNum());
            czas1 += tmp.getPj();
        } else if(czas2 <= czas3){
            this->procesor2.push_back(tmp.getNum());
            czas2 += tmp.getPj();
        }else{
            this->procesor3.push_back(tmp.getNum());
            czas3 += tmp.getPj();
        }
    }
}

void Rozwiazanie3p::LPT(Problem &dane) {
    dane.sort();
    LSA(dane);
}

void Rozwiazanie3p::PTAS(Problem &dane, double epsilon) {
    dane.sort();

    double K = dane.getN()*epsilon;

    std::vector<Zadanie> reduced_tasks;
    std::vector<Zadanie> remaining_tasks;

    for (int i = 0; i < K; ++i) {
        reduced_tasks.push_back(dane.getDane()[i]);
    }
    for (int i = K; i < dane.getN(); ++i) {
        remaining_tasks.push_back(dane.getDane()[i]);
    }

    Problem reduced;
    reduced.setDane(reduced_tasks);
    reduced.setN(reduced_tasks.size());

    Problem remaining;
    remaining.setDane(remaining_tasks);
    remaining.setN(remaining_tasks.size());
    reduced.sort();

    this->przeglad_zupelny3p(reduced);
    this->LSA(remaining);
}

void Rozwiazanie3p::programowanie_dynamiczne3p(Problem &dane) {
    double C = 0;
    for (int i = 0; i < dane.getN(); i++) {
        C += dane.getDane()[i].getPj();
    }
    int n = dane.getN();
    int Kl = (C /3) + 1;
    std::cout<<"C "<<C<<" KL "<<Kl<< std::endl;


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
    std::vector<Zadanie> nowe_dane;
    Problem Nowe_dane;
    for(int i=1;i<=n;i++){
        if(std::find(procesor1.begin(), procesor1.end(), i) == procesor1.end()){
            Zadanie tmp;
            tmp.setPj(dane.getDane()[i-1].getPj());
            tmp.setNum(i);
            nowe_dane.push_back(tmp);
        }
    }
    Nowe_dane.setDane(nowe_dane);
    Nowe_dane.setN(nowe_dane.size());


    std::vector<std::vector<int>> T2(nowe_dane.size() + 1, std::vector<int>(Kl, 0));

    for (int i = 0; i < nowe_dane.size()+1; ++i) {
        T2[i][0] = 1;
    }

    for (int i = 0; i < nowe_dane.size(); i++) {
        Zadanie tmp = Nowe_dane.getDane()[i];
        for (int k = 0; k < Kl; k++) {
            if (T2[i][k] == 1) {
                if (T2[i][tmp.getPj() + k] == 0) {
                    for (int j = i + 1; j <= nowe_dane.size(); j++) {
                        if((tmp.getPj() + k)<Kl){
                            T2[j][tmp.getPj() + k] = 1;
                        }
                    }
                }
            }
        }
        if (T2[i+1][Kl-1] == 1) {
            break;
        }
    }

    int koniec2 = 1;
    while (Kl != koniec2) {
        int znaleziono2 = 0;
        for (int j = 0; j < nowe_dane.size(); ++j) {
            if (T2[j][Kl - koniec2] == 1) {
                procesor2.push_back(Nowe_dane.getDane()[j-1].getNum());
                koniec2 += Nowe_dane.getDane()[j-1].getPj();
                znaleziono2 = 1;
                break;
            }
        }
        if (znaleziono2 == 0) {
            koniec2++;
        }
    }

    for(int i = 1; i <= n; i++) {
        if(std::find(procesor1.begin(), procesor1.end(), i) == procesor1.end() &&
           std::find(procesor2.begin(), procesor2.end(), i) == procesor2.end()) {
            procesor3.push_back(i);
        }
    }

}

void Rozwiazanie3p::displayArray(const std::vector<std::vector<int>>& T) {
    for (const auto& row : T) {
        for (int val : row) {
            std::cout << val << " ";
        }
        std::cout << std::endl;
    }
}