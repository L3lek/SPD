#include "Rozwiazanie.h"
#include <cmath>
#include <iostream>
#include <algorithm>
#include <queue>

Rozwiazanie::Rozwiazanie(double kryterium, const std::vector<int> &uszereg){
    Rozwiazanie::kryterium=kryterium;
    Rozwiazanie::uszereg=uszereg;
    Rozwiazanie::czas=10000;
}

Rozwiazanie::Rozwiazanie(){
    std::vector<int> szereg;
    Rozwiazanie::kryterium=0;
    Rozwiazanie::uszereg=szereg;
    Rozwiazanie::czas=10000;
}

double Rozwiazanie::oblicz_kryterium(Problem &dane, int i) {
    double cmax;
    if (i==0){
        Zadanie tmp=dane.getDane()[i];
        cmax= tmp.getRj() + tmp.getPj() + tmp.getQj();
    }else{
        double pop = oblicz_kryterium(dane,i-1);
        Zadanie tmp=dane.getDane()[i];
        cmax = std::max(pop - dane.getDane()[i - 1].getQj(), tmp.getRj()) + tmp.getPj() + tmp.getQj();
    }
    this->kryterium=std::max(this->kryterium, cmax);
    return cmax;
}

void Rozwiazanie::wyswietl_menu() {
    std::cout<<"Dostepne metody: "<<std::endl;
    std::cout<<"1 - sortowanie po rj "<<std::endl;
    std::cout<<"2 - sortowanie po qj "<<std::endl;
    std::cout<<"3 - Przeglad zupelny "<<std::endl;
    std::cout<<"4 - Schrage "<<std::endl;
    std::cout<<"5 - Schrage z wywłaszczeniem "<<std::endl;
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
                dane.sort_rj();
                //std::cout<<"Posortowano"<<std::endl;
                this->oblicz_kryterium(dane,dane.getDane().size()-1);
                //std::cout<<"Obliczono kryterium"<<std::endl;
                this->pobierz_kolejnosc(dane);
                // std::cout<<"Przekopiowano"<<std::endl;
                break;
            }
            case 2: {
                dane.sort_qj();
                //std::cout<<"Posortowano"<<std::endl;
                this->oblicz_kryterium(dane,dane.getDane().size()-1);
                //std::cout<<"Obliczono kryterium"<<std::endl;
                this->pobierz_kolejnosc(dane);

                // std::cout<<"Przekopiowano"<<std::endl;
                break;
            }
            case 3: {
                this->przeglad_zupelny(dane);
                break;
            }case 4: {
                this->Schrage(dane);
                break;
            }case 5: {
                this->Schrage_prmt(dane);
                break;
            }
            default:
                std::cout << "bledna opcja";
                break;
        }
}

void Rozwiazanie::generuj_permutacje(std::vector<int>& szereg, int indeks, Problem &dane) {
    if (indeks == szereg.size() - 1) {
        Rozwiazanie rozw;
        rozw.oblicz_kryterium(dane,dane.getDane().size()-1);
        if(rozw.kryterium < this->getCzas()){
            this->czas=rozw.kryterium;
            this->uszereg=szereg;
            this->kryterium=rozw.kryterium;
        }
        return;
    }

    for (int i = indeks; i < szereg.size(); ++i) {
        std::swap(szereg[indeks], szereg[i]);
        generuj_permutacje(szereg, indeks + 1, dane);
        std::swap(szereg[indeks], szereg[i]);

    }
}

void Rozwiazanie::przeglad_zupelny(Problem &dane) {
    std::vector<int> szereg;
    for (int i = 1; i <= dane.getN(); ++i) {
        szereg.push_back(i);
    }
    generuj_permutacje(szereg, 0, dane);

}

void Rozwiazanie::Schrage_prmt(Problem &dane){
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
                std::cout<<"("<<wykonywane.getNum()<<", "<<t<<")"<<std::endl;
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
    std::cout<<"Czas wykonania wynosi: "<<Cmax<<std::endl;
}

void Rozwiazanie::Schrage(Problem &dane) {
    std::vector<Zadanie> N = dane.getDane();
    std::priority_queue<Zadanie, std::vector<Zadanie>, CompareRj> N_priority_queue;
    std::priority_queue<Zadanie, std::vector<Zadanie>, CompareQj> G_priority_queue; // Kopiec G
    std::vector<int> heap; // Kopiec przechowujący indeksy elementów w kolejce priorytetowej

    double t = 0;
    double Cmax = 0;

    // Wypełnianie kolejki priorytetowej N
    for (int i = 0; i < N.size(); ++i) {
        N_priority_queue.push(N[i]);
        heap.push_back(i);
    }
    std::make_heap(heap.begin(), heap.end(), HeapComparator(N));

    // Kopiowanie elementów z N_priority_queue do kontenera, aby umożliwić iterację
    std::vector<Zadanie> N_copy;
    while (!N_priority_queue.empty()) {
        N_copy.push_back(N_priority_queue.top());
        N_priority_queue.pop();
    }
    for (int i = 0; i < N_copy.size(); ++i) {
        N_priority_queue.push(N_copy[i]);
    }

    while (!N_priority_queue.empty() || !G_priority_queue.empty()) {
        while (!N_priority_queue.empty() && N_priority_queue.top().getRj() <= t) {
            Zadanie zadanie = N_priority_queue.top();
            N_priority_queue.pop();
            heap.pop_back(); // Usunięcie indeksu z kopca
            std::make_heap(heap.begin(), heap.end(), HeapComparator(N)); // Zreorganizowanie kopca
            G_priority_queue.push(zadanie);
        }

        if (G_priority_queue.empty()) {
            if (!N_priority_queue.empty()) {
                t = N_priority_queue.top().getRj();
            }
        } else {
            Zadanie e = G_priority_queue.top();
            G_priority_queue.pop();

            t += e.getPj();
            uszereg.push_back(e.getNum());
            Cmax = std::max(Cmax, t + e.getQj());
        }
    }

    // Uwzględnienie zadań, które pozostały w N_priority_queue
    if (!N_priority_queue.empty()) {
        double najpozniejsze_qj = std::numeric_limits<double>::min();
        while (!N_priority_queue.empty()) {
            najpozniejsze_qj = std::max(najpozniejsze_qj, N_priority_queue.top().getQj());
            N_priority_queue.pop();
        }
        t += najpozniejsze_qj;
        Cmax = std::max(Cmax, t); // Aktualizacja Cmax
    }


    kryterium = Cmax;
    this->wyswietl();
}