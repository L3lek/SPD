#include "Rozwiazanie.h"
#include <iostream>
#include <vector>
#include <algorithm>
#include <chrono>
#include "Zadanie.h"
void Rozwiazanie::wyswietl_menu() {
    std::cout<<"Dostepne metody: "<<std::endl;
    std::cout<<"1 - Przegląd zupełny "<<std::endl;
    std::cout<<"2 - NEH "<<std::endl;
    std::cout<<"3 - Algorytm Johnsona "<<std::endl;
    std::cout<<"4 - FNEH"<<std::endl;
    std::cout<<"5 - Wersja podstawowa algorytmu podziału i ograniczeń (z prostym LB)"<<std::endl;
    std::cout<<"6 - Wersja zaawansowana algorytmu podziału i ograniczeń"<<std::endl;
}

double Rozwiazanie::obliczCmax(Problem& problem){
    int iloscZadan = problem.getN();
    int iloscMaszyn = problem.getM();
    std::vector<Zadanie> zadania = problem.getDane();

    std::vector<std::vector<double>> czasZakonczenia(iloscZadan + 1, std::vector<double>(iloscMaszyn + 1, 0.0));

    for(int z = 0; z < iloscMaszyn; ++z){
        if(z==0){
            for (int i = 0; i < iloscZadan; ++i) {
                if (i==0)
                    czasZakonczenia[i][z] = zadania[i].pobierzCzasNaPozycji(z);
                else
                    czasZakonczenia[i][z] = zadania[i].pobierzCzasNaPozycji(z)+czasZakonczenia[i-1][z];
            }
        }else
            for (int i = 0; i < iloscZadan; ++i) {
                if (i==0)
                    czasZakonczenia[i][z] = zadania[i].pobierzCzasNaPozycji(z)+czasZakonczenia[i][z-1];
                else
                    czasZakonczenia[i][z] = zadania[i].pobierzCzasNaPozycji(z)+std::max(czasZakonczenia[i-1][z],czasZakonczenia[i][z-1]);
            }
    }
    double Cmax = czasZakonczenia[iloscZadan-1][iloscMaszyn-1];
    return Cmax;
}

void Rozwiazanie::wyswietl() {
    std::cout<<std::endl<<"Wyliczone kryterium: "<<najlepszyCmax<<std::endl;
}

void Rozwiazanie::wyswietl_kolejnosc(){
    for(int i=0;i<najlepszaKolejka.size();i++){
        int tmp= najlepszaKolejka[i]+1;
        std::cout<<tmp <<" ";
    }
    std::cout<<std::endl;
}

void Rozwiazanie::wybierz_metode(Problem &dane) {
    int zmienna;
    std::cin >> zmienna;

    switch (zmienna) {
        case 1: {
            auto start = std::chrono::high_resolution_clock::now();
            this->przeglad_zupelny(dane);
            this->wyswietl();
            this->wyswietl_kolejnosc();
            auto end = std::chrono::high_resolution_clock::now();
            auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();
            std::cout << "Czas wykonania przeglądu zupełnego: " << duration << " ms\n";
            break;
        }
        case 2: {
            auto start = std::chrono::high_resolution_clock::now();
            this->NEH(dane);
            this->wyswietl();
            // this->wyswietl_kolejnosc();
            auto end = std::chrono::high_resolution_clock::now();
            auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();
            std::cout << "Czas wykonania metody NEH: " << duration << " ms\n";
            break;
        }
        case 3: {
            auto start = std::chrono::high_resolution_clock::now();
            this->johnson(dane);
            this->wyswietl();
            // this->wyswietl_kolejnosc();
            auto end = std::chrono::high_resolution_clock::now();
            auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();
            std::cout << "Czas wykonania algorytmu Johnsona: " << duration << " ms\n";
            break;
        }
        
        default:
            std::cout << "Błędna opcja\n";
            break;
    }
}

//
//void Rozwiazanie::NEH(Problem& problem) {
//    int iloscZadan = problem.getN();
//    std::vector<Zadanie> posortowane;
//    Problem kolejka(problem.getN(), problem.getM()); // Inicjalizacja kolejki jako obiekt klasy Problem
//    double najlepszyCmax = std::numeric_limits<double>::max();
//
//    posortowane = problem.sortujZadaniaWedlugSumyCzasow();
//
//    kolejka.wstawZadanie(posortowane[0]); // Wstawienie pierwszego zadania do kolejki
//    najlepszyCmax = obliczCmax(kolejka); // Obliczenie Cmax dla pojedynczego zadania
//
//    // Iteracyjne wstawianie pozostałych zadań
//    for (int i = 1; i < iloscZadan; ++i) {
//        Zadanie zadanie = posortowane[i]; // Pobranie kolejnego zadania
//        double aktualnyCmax = 0;
//        Problem najlepszaKolejka(problem.getN(), problem.getM()); // Inicjalizacja najlepszej kolejki
//
//        // Wstawianie zadania na każdą możliwą pozycję w kolejce
//        for (size_t j = 0; j <= kolejka.rozmiar(); ++j) {
//            Problem nowaKolejka = kolejka; // Skopiowanie aktualnej kolejki
//            nowaKolejka.wstawZadanieNaPozycji(zadanie, j); // Wstawienie zadania na pozycji j
//            double CmaxNowejKolejki = obliczCmax(nowaKolejka); // Obliczenie Cmax dla nowej kolejki
//
//            // Aktualizacja najlepszej kolejki i najlepszego Cmax
//            if (CmaxNowejKolejki < najlepszyCmax) {
//                najlepszyCmax = CmaxNowejKolejki;
//                najlepszaKolejka = nowaKolejka;
//            }
//        }
//
//        // Ustawienie najlepszej kolejności dla następnego wstawiania zadania
//        kolejka = najlepszaKolejka;
//    }
//}

void Rozwiazanie::NEH(Problem &problem) {
    int iloscZadan = problem.getN();
    std::vector<Zadanie> posortowane;
    najlepszaKolejka.clear();
    najlepszyCmax = std::numeric_limits<double>::max();

    posortowane = problem.sortujZadaniaWedlugSumyCzasow();

    Problem kolejka(problem.getN(), problem.getM());
    kolejka.wstawZadanie(posortowane[0]);
    najlepszaKolejka.push_back(posortowane[0].getNum());
    najlepszyCmax = obliczCmax(kolejka);


    for (int i = 1; i < iloscZadan; ++i) {
        Zadanie zadanie = posortowane[i];
        double aktualnyCmax = 0;
        Problem najlepszakolejka(problem.getN(), problem.getM());

        for (size_t j = 0; j <= kolejka.rozmiar(); ++j) {
            Problem nowaKolejka = kolejka;
            nowaKolejka.wstawZadanieNaPozycji(zadanie, j);
            double CmaxNowejKolejki = obliczCmax(nowaKolejka);


            if (CmaxNowejKolejki < najlepszyCmax) {
                najlepszyCmax = CmaxNowejKolejki;
                najlepszakolejka = nowaKolejka;
            }
        }

        kolejka = najlepszakolejka;
        najlepszaKolejka.clear();
        for (int k = 0; k < kolejka.rozmiar(); ++k) {
            najlepszaKolejka.push_back(kolejka.getDane()[k].getNum());
        }
    }
}

void Rozwiazanie::przeglad_zupelny(Problem &problem) {
    std::vector<Zadanie> perm = problem.getDane();
    std::vector<int> indeksy;
    double czas = std::numeric_limits<double>::max();

    for (int i = 0; i < problem.getN(); ++i) {
        indeksy.push_back(i);
    }

    do {
        Problem temp_problem = problem;
        std::vector<Zadanie> noweDane;
        for (int i : indeksy) {
            noweDane.push_back(perm[i]);
        }
        temp_problem.setDane(noweDane);

        double wylicz_czas = this->obliczCmax(temp_problem);
        if (wylicz_czas < czas) {
            czas = wylicz_czas;
            this->najlepszyCmax = wylicz_czas;
            this->najlepszaKolejka = indeksy;
        }

    } while (std::next_permutation(indeksy.begin(), indeksy.end()));
}

// Implementacja algorytmu Johnsona
void Rozwiazanie::johnson(Problem &problem) {
    if (problem.getM() != 2) {
        std::cerr << "Algorytm Johnsona działa tylko dla problemów z dwiema maszynami." << std::endl;
        return;
    }

    std::vector<Zadanie> JL; // Zbiór zadań z czasami na pierwszej maszynie mniejszymi lub równymi na drugiej
    std::vector<Zadanie> JR; // Zbiór zadań z czasami na drugiej maszynie mniejszymi od pierwszej

    const std::vector<Zadanie> &zadania = problem.getDane();
    for (const auto &zadanie : zadania) {
        if (zadanie.getTasks()[0] <= zadanie.getTasks()[1]) {
            JL.push_back(zadanie);
        } else {
            JR.push_back(zadanie);
        }
    }

    // Sortowanie zadań w JL według niemalejących czasów na pierwszej maszynie
    std::sort(JL.begin(), JL.end(), [](const Zadanie &a, const Zadanie &b) {
        return a.getTasks()[0] < b.getTasks()[0];
    });

    // Sortowanie zadań w JR według nierosnących czasów na drugiej maszynie
    std::sort(JR.begin(), JR.end(), [](const Zadanie &a, const Zadanie &b) {
        return a.getTasks()[1] > b.getTasks()[1];
    });

    // Konkatenacja JL i JR tworząca optymalne uszeregowanie
    std::vector<Zadanie> pi;
    pi.insert(pi.end(), JL.begin(), JL.end());
    pi.insert(pi.end(), JR.begin(), JR.end());

    // Aktualizacja najlepszej kolejki i Cmax
    problem.setDane(pi);
    double najlepszyCmax = obliczCmax(problem);
    setNajlepszyCmax(najlepszyCmax);
}