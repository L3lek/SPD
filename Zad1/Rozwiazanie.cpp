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

double Rozwiazanie::oblicz_kryterium(Problem &dane, int i) {
    double cmax;
    Zadanie tmp=dane.getDane()[i];
    if (i==0){
        cmax= tmp.getRj() + tmp.getPj();
    }else{
        double pop = oblicz_kryterium(dane,i-1);
        cmax = std::max(pop, tmp.getRj()) + tmp.getPj();
    }
    this->kryterium=std::max(this->kryterium, cmax+tmp.getQj());
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
    std::cout<<"7 - losowa kolejnosc "<<std::endl;
    std::cout<<"8 - Carlier "<<std::endl;
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
                this->oblicz_kryterium(dane,dane.getDane().size()-1);
                this->pobierz_kolejnosc(dane);
                auto end = std::chrono::high_resolution_clock::now();
                auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();
                std::cout << "Czas wykonania: " << duration << " ms" << std::endl;
                break;
            }
            case 2: {
                auto start = std::chrono::high_resolution_clock::now();
                dane.sort_qj();
                this->oblicz_kryterium(dane,dane.getDane().size()-1);
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
                this->oblicz_kryterium(dane,dane.getDane().size()-1);
                this->pobierz_kolejnosc(dane);
                auto end = std::chrono::high_resolution_clock::now();
                auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();
                std::cout << "Czas wykonania: " << duration << " ms" << std::endl;
                break;
            }
            case 7: {
                dane.losowo();
                this->oblicz_kryterium(dane,dane.getDane().size()-1);
                this->pobierz_kolejnosc(dane);
                break;
            }
            case 8: {
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
    // this->wyswietl();
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
    double t = 0, Cmax = 0, czas_zakonczenia;
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
                // std::cout<<"("<<wykonywane.getNum()<<", "<<t<<")"<<std::endl;
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
    // std::cout<<"Czas wykonania wynosi: "<<Cmax<<std::endl;
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

int find_b(std::vector<Zadanie>& dane, int C_max) {
    int b = -1;
    for (int j = dane.size() - 1; j >= 0; j--) {
        if (C_max == dane[j].getRj() + dane[j].getQj()) {
            b = j;
            return b;
        }
    }
    return -1;
}

int find_a(std::vector<Zadanie>& dane, int C_max, int b) {
    int a = -1;
    int sum = 0;
    for (int j = 0; j <= b; j++) {
        sum = 0;
        for (int s = j; s <= b; s++) {
            sum += dane[s].getPj();
        }
        if (C_max == (dane[j].getRj() + sum + dane[b].getQj())) {
            a = j;
            return a;
        }
    }
    return -1;
}

int find_c(std::vector<Zadanie>& dane, int b, int a) {
    int c = -1;
    for (int j = b; j >= a; j--) {
        if (dane[j].getQj() < dane[b].getQj()) {
            c = j;
            return c;
        }
    }
    return -1;
}

double Rozwiazanie::Carlier(Problem& problem, double UB) {
    std::vector<Zadanie> PI = problem.getDane();
    double U = 0;
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
    int nr_ref = 0;
    
    U = Schrage(problem);
    uporzadkuj_dane(problem);

    if (U < UB) {
        UB = U;
    }

    b = find_b(problem.getDane(), U);
    a = find_a(problem.getDane(), U, b);
    c = find_c(problem.getDane(), b, a);

    if (c == -1) {
        return UB;
    }

    for (int j = c + 1; j <= b; j++) {
        r_prim = std::min(r_prim, problem.getDane()[j].getRj());
        q_prim = std::min(q_prim, problem.getDane()[j].getQj());
        p_prim += problem.getDane()[j].getPj();
    }
    double h = r_prim + q_prim + p_prim;
    for (int j = c; j <= b; j++) {
        r = std::min(r_prim, problem.getDane()[j].getRj());
        q = std::min(q_prim, problem.getDane()[j].getQj());
        p += problem.getDane()[j].getPj();
    }
    double h_2 = r + q + p;

    nr_ref = problem.getDane()[c].getNum();
    r_ref = problem.getDane()[c].getRj();
    
    problem.getDane()[c].setRj(std::max(problem.getDane()[c].getRj(), r_prim + p_prim));

    LB = this->Schrage_pmtn(problem);

    if (LB < UB) {
        UB = Carlier(problem, UB);
    }

    for (int j = 0; j < problem.getDane().size(); j++) {
        if (nr_ref == problem.getDane()[j].getNum()) {
            problem.getDane()[j].setRj(r_ref);
        }
    }

    nr_ref = problem.getDane()[c].getNum();
    q_ref = problem.getDane()[c].getQj();

    problem.getDane()[c].setQj(std::max(problem.getDane()[c].getQj(), q_prim + p_prim));

    LB = this->Schrage_pmtn(problem);

    if (LB < UB) {
        UB = Carlier(problem, UB);
    }

    for (int j = 0; j < problem.getDane().size(); j++) {
        if (nr_ref == problem.getDane()[j].getNum()) {
            problem.getDane()[j].setQj(q_ref);
        }
    }

    return UB;
}

