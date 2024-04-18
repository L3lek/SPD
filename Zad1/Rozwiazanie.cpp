#include "Rozwiazanie.h"
#include <cmath>
#include <iostream>
#include <algorithm>
#include <queue>
#include <chrono>

Rozwiazanie::Rozwiazanie(double kryterium, const std::vector<int> &uszereg){
    Rozwiazanie::kryterium=kryterium;
    Rozwiazanie::uszereg=uszereg;
}
Rozwiazanie::Rozwiazanie(){
    std::vector<int> szereg;
    Rozwiazanie::kryterium=0;
    Rozwiazanie::uszereg=szereg;
}

double Rozwiazanie::oblicz_kryterium(Problem &dane) {
    double cmax=0,pom=0;
    for(int i=0;i<dane.getDane().size();i++){
        if (i==0){
            pom= dane.getDane()[i].getRj() + dane.getDane()[i].getPj();
            cmax = std::max(cmax,pom+dane.getDane()[i].getQj());
        }else{
            pom = std::max(pom, dane.getDane()[i].getRj()) + dane.getDane()[i].getPj();
            cmax = std::max(cmax,pom+dane.getDane()[i].getQj());
        }
    }
    return cmax;
}

void Rozwiazanie::wyswietl_menu() {
    std::cout<<"Dostepne metody: "<<std::endl;
    std::cout<<"1 - sortowanie po rj "<<std::endl;
    std::cout<<"2 - sortowanie po qj "<<std::endl;
    std::cout<<"3 - Przeglad zupelny "<<std::endl;
    std::cout<<"4 - Schrage "<<std::endl;
    std::cout<<"5 - Schrage z wywlaszczeniem "<<std::endl;
    std::cout<<"6 - sortowanie po qj + pj "<<std::endl;
    std::cout<<"7 - Carlier "<<std::endl;
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
    std::cout<<"wybierz metode    ";
    int zmienna=100;
    std::cin>>zmienna;
        switch (zmienna) {
            case 1: {
                auto start = std::chrono::high_resolution_clock::now();
                dane.sort_rj();
                kryterium=oblicz_kryterium(dane);
                this->pobierz_kolejnosc(dane);
                auto end = std::chrono::high_resolution_clock::now();
                auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();
                std::cout << "Czas wykonania: " << duration << " ms" << std::endl;
                break;
            }
            case 2: {
                auto start = std::chrono::high_resolution_clock::now();
                dane.sort_qj();
                kryterium=oblicz_kryterium(dane);
                this->pobierz_kolejnosc(dane);
                auto end = std::chrono::high_resolution_clock::now();
                auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();
                std::cout << "Czas wykonania: " << duration << " ms" << std::endl;
                break;
            }
            case 3: {
                auto start = std::chrono::high_resolution_clock::now();
                this->przeglad_zupelny(dane);
                auto end = std::chrono::high_resolution_clock::now();
                auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();
                std::cout << "Czas wykonania: " << duration << " ms" << std::endl;
                break;
            }
            case 4: {
                auto start = std::chrono::high_resolution_clock::now();
                kryterium=Schrage(dane);
                auto end = std::chrono::high_resolution_clock::now();
                auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();
                std::cout << "Czas wykonania: " << duration << " ms" << std::endl;
                break;
            }case 5: {
                auto start = std::chrono::high_resolution_clock::now();
                kryterium=Schrage_pmtn(dane);
                auto end = std::chrono::high_resolution_clock::now();
                auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();
                std::cout << "Czas wykonania: " << duration << " ms" << std::endl;
                break;
            }
            case 6: {
                auto start = std::chrono::high_resolution_clock::now();
                dane.sort_qp();
                kryterium=oblicz_kryterium(dane);
                this->pobierz_kolejnosc(dane);
                auto end = std::chrono::high_resolution_clock::now();
                auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();
                std::cout << "Czas wykonania: " << duration << " ms" << std::endl;
                break;
            }
            case 7: {
                double UB = std::numeric_limits<double>::infinity();
                auto start = std::chrono::high_resolution_clock::now();
                kryterium=Carlier(dane,UB);
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

double Rozwiazanie::Schrage(Problem &dane) {
    std::vector<Zadanie> Dane = dane.getDane();
    std::priority_queue<Zadanie, std::vector<Zadanie>, CompareRj> N;
    std::priority_queue<Zadanie, std::vector<Zadanie>, CompareQj> G;
    double t = 0;
    double Cmax = 0;

    uszereg.clear();

    for (int i = 0; i < Dane.size(); ++i) {
        N.push(Dane[i]);
    }
    

    while (!N.empty() || !G.empty()) {
        while (!N.empty() && N.top().getRj() <= t) {
            Zadanie zadanie = N.top();
            N.pop();
            G.push(zadanie);
        }

        if (G.empty()) {
            if (!N.empty()) {
                t = N.top().getRj();
            }
        } else {
            Zadanie pom = G.top();
            G.pop();

            t += pom.getPj();
            uszereg.push_back(pom.getNum());
            Cmax = std::max(Cmax, t + pom.getQj());
        }
    }

    return Cmax;
}

void Rozwiazanie::przeglad_zupelny(Problem& dane) {
    std::vector<Zadanie> perm = dane.getDane();
    std::vector<int> indeksy;
    double czas=std::numeric_limits<double>::max();

    for (int i = 0; i < dane.getN(); ++i) {
        indeksy.push_back(perm[i].getNum());
    }

    do {
        double wylicz_czas = dane.licz_czas(indeksy);
        if (wylicz_czas < czas) {
            czas = wylicz_czas;
            this->kryterium = wylicz_czas;
            this->uszereg=indeksy;

        }
    } while (std::next_permutation(indeksy.begin(), indeksy.end()));
}

double Rozwiazanie::Schrage_pmtn(Problem &dane){
    double t = 0, Cmax = 0, czas_zakonczenia=0;
    int ip=0;
    bool przyjechało = false;
    std::vector<Zadanie> Gotowe;
    dane.sort_rj();
    std::vector<Zadanie> Zadania=dane.getDane();

    while (!Gotowe.empty() || !Zadania.empty()){
        while (!Zadania.empty()) {
            if(Zadania[0].getRj()>t){
                break;
            }
            Zadanie kolejne = Zadania[0];
            if(kolejne.getRj()<=t){
                for (size_t i = 1; i < Zadania.size(); ++i) {
                    const Zadanie& j = Zadania[i];
                    if (j.getRj() <= t && j.getQj() > kolejne.getQj()) {
                        kolejne = j;
                    }
                }
                Gotowe.push_back(kolejne);
                Zadania.erase(std::remove(Zadania.begin(), Zadania.end(), kolejne), Zadania.end());
                przyjechało = true;
            }
        }

        if(przyjechało){
            Problem tmp(Gotowe.size(),Gotowe);
            tmp.sort_qj();
            Gotowe=tmp.getDane();
            przyjechało=false;
        }

        if (!Gotowe.empty()) {
            Zadanie& wykonywane = Gotowe[0];

            if(wykonywane.getNum()!=ip){
                ip=wykonywane.getNum();
            }
            wykonywane.setPj(wykonywane.getPj()-1);

            if(wykonywane.getPj()==0){
                czas_zakonczenia=t+1;
                Cmax=std::max(Cmax,czas_zakonczenia+wykonywane.getQj());
                Gotowe.erase(Gotowe.begin());
            }
        }
        t++;
    }

    return Cmax;
}

///////////////////////////////////////////////////////////////////////////////////

void Rozwiazanie::uporzadkuj_dane(Problem &dane) {
    std::vector<Zadanie> posortowane_dane;

    for (int i = 0; i < uszereg.size(); ++i) {
        int num = uszereg[i];

        for (int j = 0; j < dane.getDane().size(); ++j) {
            if (dane.getDane()[j].getNum() == num) {
                posortowane_dane.push_back(dane.getDane()[j]);
                break;
            }
        }
    }

    dane.setDane(posortowane_dane);
}

int Rozwiazanie::find_b(Problem& dane, int C_max) {
    int b = -1;
    double C=0;
    for(int i=0;i<dane.getDane().size();i++){
        if (i==0){
            C= dane.getDane()[i].getRj() + dane.getDane()[i].getPj();
        }else{
            C = std::max(C, dane.getDane()[i].getRj()) + dane.getDane()[i].getPj();
        }
    }

    for (int j = dane.getDane().size()-1; j >=0 ; j--) {
        if (C_max == C + dane.getDane()[j].getQj()) {
            b = j;
            return b;
        }
        C=C-dane.getDane()[j].getPj();
    }
    return b;
}

int Rozwiazanie::find_a(Problem& dane, int C_max, int b) {
    int a = 0;
    int sum = 0;
    for (int j = 0; j <= b; j++) {
        sum = 0;
        for (int s = j; s <= b; s++) {
            sum += dane.getDane()[s].getPj();
        }
        if (C_max == (dane.getDane()[j].getRj() + sum + dane.getDane()[b].getQj())) {
            a = j;
            return a;
        }
    }
    return 0;
}

int Rozwiazanie::find_c(Problem& dane, int b, int a) {
    int c = -1;

    for (int j = a; j <= b; j++) {
        if (dane.getDane()[j].getQj() < dane.getDane()[b].getQj()) {
            c = j;
            return c;
        }
    }
    return c;
}

double Rozwiazanie::Carlier(Problem& problem, double UB) {
    Problem wzor=problem;
    double U = 0;
    double UB_min= std::numeric_limits<double>::infinity();
    double LB = 0;
    int a = -1;
    int b = -1;
    int c = -1;
    double r_prim = std::numeric_limits<double>::infinity();
    double p_prim = 0;
    double q_prim = std::numeric_limits<double>::infinity();
    double r = std::numeric_limits<double>::infinity();
    double p = 0;
    double q = std::numeric_limits<double>::infinity();
    double r_ref = 0;
    double q_ref = 0;
    int nr_ref_r = 0,nr_ref_q = 0;

    U = Schrage(problem);
    uporzadkuj_dane(problem);

    if (U < UB) {
        UB = U;
    }

    // std::cout<<UB<<std::endl;
    // for(int i=0;i<uszereg.size();i++){
    //     std::cout<<uszereg[i]<<" ";
    // }
    // std::cout<<std::endl;

    b = find_b(problem, U);  
    a = find_a(problem, U, b);
    c = find_c(problem, b, a);

    if (c == -1) {
        return UB;
    }

    for (int j = c + 1; j <= b; j++) {
        r_prim = std::min(r_prim, problem.getDane()[j].getRj());
        q_prim = std::min(q_prim, problem.getDane()[j].getQj());
        p_prim += problem.getDane()[j].getPj();
    }

    r_ref = problem.getDane()[c].getRj();
    nr_ref_r= problem.getDane()[c].getNum();

    problem.getDane()[c].setRj(std::max(problem.getDane()[c].getRj(), r_prim + p_prim));

    LB= this->Schrage_pmtn(problem);

    if (LB < UB) {
        UB = Carlier(problem, UB);
    }

    problem.getDane()[c].setRj(r_ref);

    q_ref = problem.getDane()[c].getQj();
    nr_ref_q= problem.getDane()[c].getNum();

    problem.getDane()[c].setQj(std::max(problem.getDane()[c].getQj(), q_prim + p_prim));

    LB = this->Schrage_pmtn(problem);
    if (LB < UB) {
        UB = Carlier(problem, UB);
    }


    problem.getDane()[c].setQj(q_ref);


    return UB;
}