#include "Rozwiazanie.h"
#include <iostream>
#include <vector>
#include <algorithm>
#include <chrono>
#include <cmath>
#include <queue>
#include <random>

void Rozwiazanie::wyswietl_menu() {
    std::cout<<"Dostepne metody: "<<std::endl;
    std::cout<<"1 - Przegląd zupełny "<<std::endl;
    std::cout<<"2 - NEH "<<std::endl;
    std::cout<<"3 - Algorytm Johnsona "<<std::endl;
    std::cout<<"4 - FNEH"<<std::endl;
    std::cout<<"5 - Wersja podstawowa algorytmu podziału i ograniczeń (z prostym LB)"<<std::endl;
    std::cout<<"6 - Symulowane wyżarzanie"<<std::endl;
    std::cout<<"7 - Algorytm akceptacji progu"<<std::endl;
    std::cout<<"8 - Przeszukiwanie ze zmiennym sąsiedztwem"<<std::endl;
    std::cout<<"9 - Tabu Search"<<std::endl;
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
    //    case 4: {
    //        auto start = std::chrono::high_resolution_clock::now();
    //        this->FNEH(dane);
    //        this->wyswietl();
    //        // this->wyswietl_kolejnosc();
    //        auto end = std::chrono::high_resolution_clock::now();
    //        auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();
    //        std::cout << "Czas wykonania metody QNEH: " << duration << " ms\n";
    //        break;
    //    }
        case 5: {
            auto start = std::chrono::high_resolution_clock::now();
            this->initBranchAndBound(dane);
            this->wyswietl();
            //this->wyswietl_kolejnosc();
            auto end = std::chrono::high_resolution_clock::now();
            auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();
            std::cout << "Czas wykonania algorytmu BranchAndBound - wersji podstawowej: " << duration << " ms\n";
            break;
        }
        case 6: {
            auto start = std::chrono::high_resolution_clock::now();
            this->symulowaneWyzarzanie(dane);
            this->wyswietl();
            //this->wyswietl_kolejnosc();
            auto end = std::chrono::high_resolution_clock::now();
            auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();
            std::cout << "Czas wykonania symulowanego wyżarzania: " << duration << " ms\n";
            break;
        }
        case 7: {
            auto start = std::chrono::high_resolution_clock::now();
            thresholdAccepting(dane);
            this->wyswietl();
            //this->wyswietl_kolejnosc();
            auto end = std::chrono::high_resolution_clock::now();
            auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();
            std::cout << "Czas wykonania progu akceptacji: " << duration << " ms\n";
            break;
        }
        case 8: {
            auto start = std::chrono::high_resolution_clock::now();
            variableNeighborhoodSearch(dane);
            this->wyswietl();
            //this->wyswietl_kolejnosc();
            auto end = std::chrono::high_resolution_clock::now();
            auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();
            std::cout << "Czas wykonania przeszukania ze zmiennym  sąsiedztwem: " << duration << " ms\n";
            break;
        }
        case 9: {
            auto start = std::chrono::high_resolution_clock::now();
            tabuSearch(dane);
            this->wyswietl();
            //this->wyswietl_kolejnosc();
            auto end = std::chrono::high_resolution_clock::now();
            auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();
            std::cout << "Czas wykonania przeszukania ze zmiennym  sąsiedztwem: " << duration << " ms\n";
            break;
        }
        
        default:
            std::cout << "Błędna opcja\n";
            break;
    }
}

Problem Rozwiazanie::NEH(Problem& problem) {
    std::vector<Zadanie> sortedDane = problem.sortujZadaniaWedlugSumyCzasowMalejąco();
    Problem partialProblem(0, problem.getM());

    partialProblem.wstawZadanieNaPozycji(sortedDane[0], 0);

    for (size_t i = 1; i < sortedDane.size(); ++i) {
        double bestCmax = INT_MAX;
        int bestPos = 0;
        for (int j = 0; j <= i; ++j) {
            Problem tempProblem = partialProblem;
            tempProblem.wstawZadanieNaPozycji(sortedDane[i], j);
            tempProblem.setN(i+1);
            double currentCmax = obliczCmax(tempProblem);
            if (currentCmax < bestCmax) {
                bestCmax = currentCmax;
                bestPos = j;
            }
        }
        partialProblem.wstawZadanieNaPozycji(sortedDane[i], bestPos);
    }

    partialProblem.setN(sortedDane.size());
    najlepszyCmax = obliczCmax(partialProblem);
    najlepszaKolejka.clear();
    for (std::vector<Zadanie>::const_iterator it = partialProblem.getDane().begin(); it != partialProblem.getDane().end(); ++it) {
        najlepszaKolejka.push_back(it->getNum());
    }
    return partialProblem;
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
        std::cout<<wylicz_czas<<std::endl;
        if (wylicz_czas < czas) {
            czas = wylicz_czas;
            this->najlepszyCmax = wylicz_czas;
            this->najlepszaKolejka = indeksy;
        }

    } while (std::next_permutation(indeksy.begin(), indeksy.end()));
}

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

void Rozwiazanie::FNEH(Problem& problem) {
    std::vector<Zadanie> sortedDane = problem.sortujZadaniaWedlugSumyCzasowRosnąco();
    Problem partialProblem(0, problem.getM());

    partialProblem.wstawZadanieNaPozycji(sortedDane[0], 0);

    for (size_t i = 1; i < sortedDane.size(); ++i) {
        double bestCmax = INT_MAX;
        int bestPos = 0;

        // Optymalizacja: Pomijanie niepotrzebnych obliczeń
        double currentCmax = obliczCmax(partialProblem);
        if (currentCmax < bestCmax) {
            bestCmax = currentCmax;
        }

        for (int j = 0; j <= i; ++j) {
            Problem tempProblem = partialProblem;
            tempProblem.wstawZadanieNaPozycji(sortedDane[i], j);
            tempProblem.setN(i+1);
            // Pominięto ponowne obliczanie Cmax, ponieważ zrobiliśmy to wcześniej
            if (currentCmax == INT_MAX) {
                currentCmax = obliczCmax(tempProblem);
            }
            if (currentCmax < bestCmax) {
                bestCmax = currentCmax;
                bestPos = j;
            }
        }
        partialProblem.wstawZadanieNaPozycji(sortedDane[i], bestPos);
    }

    partialProblem.setN(sortedDane.size());
    najlepszyCmax = obliczCmax(partialProblem);
    najlepszaKolejka.clear();
    for (std::vector<Zadanie>::const_iterator it = partialProblem.getDane().begin(); it != partialProblem.getDane().end(); ++it) {
        najlepszaKolejka.push_back(it->getNum());
    }
}

double Rozwiazanie::lowerBound(Problem &N, Problem &Pi) {
    double lb = 0;
    std::vector<Zadanie> Pi_copy = Pi.getDane();

    for (int i = 0; i < N.getM(); i++) {
        double sum = 0;
        for (int j = 0; j < Pi_copy.size(); j++) {
            sum += Pi_copy[j].getTasks()[i];
        }

        double lastEnd = Pi_copy[Pi_copy.size() - 1].getTasks()[i];
        lb = std::max(lastEnd + sum, lb);
    }
    return lb;
}

void Rozwiazanie::BranchAndBound(int j, Problem &N, double &ub, Problem &Pi) {
    Pi.wstawZadanie(N.getDane()[j]);
    std::vector<Zadanie> N_copy = N.getDane();

    N_copy.erase(N_copy.begin() + j);
    Problem N_COPY( N_copy.size(), N.getM(), N_copy);
    if (!N_copy.empty()) {
        double lb = lowerBound(N_COPY, Pi);
        if (lb < ub) {
            for (int i = 0; i < N_copy.size(); i++) {
                BranchAndBound(i, N_COPY, ub, Pi);
            }
        }
    } else {
        Pi.setN(Pi.getDane().size());
        Pi.setM(N.getM());
        double Cmax = this->obliczCmax(Pi);
        if (Cmax < ub) {
            ub = Cmax;
            for (std::vector<Zadanie>::const_iterator it = Pi.getDane().begin(); it != Pi.getDane().end(); ++it) {
                this->najlepszaKolejka.push_back(it->getNum());
            }
            this->setNajlepszyCmax(ub);
        }
    }
}

void Rozwiazanie::initBranchAndBound(Problem &N) {
    double ub = obliczCmax(N);

    this->setNajlepszyCmax(ub);
    for (int j = 0; j < N.rozmiar(); ++j) {
        Problem Pi;
        BranchAndBound(j, N, ub, Pi);
    }
}

void Rozwiazanie::symulowaneWyzarzanie(Problem &problem) {
    double temperaturaPoczatkowa = 100000;
    double temperaturaKoncowa = 0.0001;
    double wspolczynnikChlodzenia = 0.9999;

    std::srand(std::time(nullptr));

    Problem pocz_prob = NEH(problem);

    // for(int i=0;i<problem.getDane().size();i++){
    //      std::cout<<problem.getDane()[i].getNum()<<" ";
    // }
    // std::cout<<std::endl;

    std::vector<int> obecnaKolejka(pocz_prob.getDane().size());
    for (int i = 0; i < problem.getDane().size(); ++i) {
        obecnaKolejka[i] = pocz_prob.getDane()[i].getNum();
    }


    setNajlepszaKolejka(obecnaKolejka);
    double obecnyCmax = obliczCmax(pocz_prob);

    najlepszaKolejka = obecnaKolejka;
    najlepszyCmax = obecnyCmax;

    double temperatura = temperaturaPoczatkowa;

    while (temperatura > temperaturaKoncowa) {
        std::vector<int> nowaKolejka = obecnaKolejka;
        int i = std::rand() % nowaKolejka.size();
        int j = std::rand() % nowaKolejka.size();
        std::swap(nowaKolejka[i], nowaKolejka[j]);

        Problem pom_problem=pocz_prob;
         std::vector<Zadanie> tmp;
        for(int i=0;i<nowaKolejka.size();i++){
            for(int j=0;j<problem.getDane().size();j++){
                if (nowaKolejka[i]==problem.getDane()[j].getNum()){
                    tmp.push_back(problem.getDane()[j]);
                }   
            }
        }

        pom_problem.setDane(tmp);
        double nowyCmax = obliczCmax(pom_problem);
        // std::cout<<nowyCmax<<" - "<< obecnyCmax<<std::endl;
        if (nowyCmax < obecnyCmax || std::exp((obecnyCmax - nowyCmax) / temperatura) > ((double) std::rand() / RAND_MAX)) {
            obecnaKolejka = nowaKolejka;
            obecnyCmax = nowyCmax;

            if (nowyCmax < najlepszyCmax) {
                najlepszaKolejka = nowaKolejka;
                najlepszyCmax = nowyCmax;
            }
        }

        temperatura *= wspolczynnikChlodzenia;
    }

    setNajlepszaKolejka(najlepszaKolejka);
    setNajlepszyCmax(najlepszyCmax);
}

void Rozwiazanie::thresholdAccepting(Problem &problem) {
    double thresholdPoczatkowy = 1000;
    double thresholdKoncowy = 0.0001;
    double wspolczynnikZmniejszania = 0.9999;
    int maxIterations = 1000000;

    std::srand(std::time(nullptr));

    Problem pocz_prob = NEH(problem);

    std::vector<int> obecnaKolejka(pocz_prob.getDane().size());
    for (int i = 0; i < problem.getDane().size(); ++i) {
        obecnaKolejka[i] = pocz_prob.getDane()[i].getNum();
    }

    setNajlepszaKolejka(obecnaKolejka);
    double obecnyCmax = obliczCmax(pocz_prob);

    najlepszaKolejka = obecnaKolejka;
    najlepszyCmax = obecnyCmax;

    double threshold = thresholdPoczatkowy;

    for (int iter = 0; iter < maxIterations; ++iter) {
        std::vector<int> nowaKolejka = obecnaKolejka;
        int i = std::rand() % nowaKolejka.size();
        int j = std::rand() % nowaKolejka.size();
        std::swap(nowaKolejka[i], nowaKolejka[j]);

        Problem pom_problem = pocz_prob;
        std::vector<Zadanie> tmp;
        for (int k = 0; k < nowaKolejka.size(); ++k) {
            for (int l = 0; l < problem.getDane().size(); ++l) {
                if (nowaKolejka[k] == problem.getDane()[l].getNum()) {
                    tmp.push_back(problem.getDane()[l]);
                }
            }
        }

        pom_problem.setDane(tmp);
        double nowyCmax = obliczCmax(pom_problem);

        if (nowyCmax < obecnyCmax || std::abs(nowyCmax - obecnyCmax) <= threshold) {
            obecnaKolejka = nowaKolejka;
            obecnyCmax = nowyCmax;

            if (nowyCmax < najlepszyCmax) {
                najlepszaKolejka = nowaKolejka;
                najlepszyCmax = nowyCmax;
            }
        }

        threshold *= wspolczynnikZmniejszania;
        if (threshold < thresholdKoncowy) {
            break;
        }
    }

    setNajlepszaKolejka(najlepszaKolejka);
    setNajlepszyCmax(najlepszyCmax);
}

std::vector<std::vector<int>> Rozwiazanie::generujSasiedztwo(const std::vector<int> &kolejka, int typSasiedztwa) {
    std::vector<std::vector<int>> sasiedztwo;
    int n = kolejka.size();

    if (typSasiedztwa == 1) {
        // Swap neighborhood
        for (int i = 0; i < n - 1; ++i) {
            for (int j = i + 1; j < n; ++j) {
                std::vector<int> nowaKolejka = kolejka;
                std::swap(nowaKolejka[i], nowaKolejka[j]);
                sasiedztwo.push_back(nowaKolejka);
            }
        }
    } else if (typSasiedztwa == 2) {
        // Insert neighborhood
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j) {
                if (i != j) {
                    std::vector<int> nowaKolejka = kolejka;
                    int temp = nowaKolejka[i];
                    nowaKolejka.erase(nowaKolejka.begin() + i);
                    nowaKolejka.insert(nowaKolejka.begin() + j, temp);
                    sasiedztwo.push_back(nowaKolejka);
                }
            }
        }
    } else if (typSasiedztwa == 3) {
        // Inversion neighborhood
        for (int i = 0; i < n - 1; ++i) {
            for (int j = i + 1; j < n; ++j) {
                std::vector<int> nowaKolejka = kolejka;
                std::reverse(nowaKolejka.begin() + i, nowaKolejka.begin() + j + 1);
                sasiedztwo.push_back(nowaKolejka);
            }
        }
    }

    return sasiedztwo;
}

void Rozwiazanie::variableNeighborhoodSearch(Problem &problem) {
    int maxIterations = 500;
    int maxNeighborhoods = 2;

    std::srand(std::time(nullptr));

    Problem pocz_prob = NEH(problem);

    std::vector<int> obecnaKolejka(pocz_prob.getDane().size());
    for (int i = 0; i < problem.getDane().size(); ++i) {
        obecnaKolejka[i] = pocz_prob.getDane()[i].getNum();
    }

    setNajlepszaKolejka(obecnaKolejka);
    double obecnyCmax = obliczCmax(pocz_prob);

    najlepszaKolejka = obecnaKolejka;
    najlepszyCmax = obecnyCmax;

    int iterations = 0;

    while (iterations < maxIterations) {
        int k = 1;

        while (k <= maxNeighborhoods) {
            std::vector<std::vector<int>> sasiedztwo = generujSasiedztwo(obecnaKolejka, k);
            std::vector<int> najlepszyKandydat = obecnaKolejka;
            double najlepszyKandydatCmax = obecnyCmax;

            for (const auto &kandydat : sasiedztwo) {
                Problem pom_problem = pocz_prob;
                std::vector<Zadanie> tmp;
                for (int i = 0; i < kandydat.size(); ++i) {
                    for (int j = 0; j < problem.getDane().size(); ++j) {
                        if (kandydat[i] == problem.getDane()[j].getNum()) {
                            tmp.push_back(problem.getDane()[j]);
                        }
                    }
                }

                pom_problem.setDane(tmp);
                double kandydatCmax = obliczCmax(pom_problem);

                if (kandydatCmax < najlepszyKandydatCmax) {
                    najlepszyKandydat = kandydat;
                    najlepszyKandydatCmax = kandydatCmax;
                }
            }

            if (najlepszyKandydatCmax < obecnyCmax) {
                obecnaKolejka = najlepszyKandydat;
                obecnyCmax = najlepszyKandydatCmax;
                k = 1;
            } else {
                ++k;
            }
        }

        if (obecnyCmax < najlepszyCmax) {
            najlepszaKolejka = obecnaKolejka;
            najlepszyCmax = obecnyCmax;
        }

        ++iterations;
    }

    setNajlepszaKolejka(najlepszaKolejka);
    setNajlepszyCmax(najlepszyCmax);
}

void Rozwiazanie::tabuSearch(Problem &problem) {
    int tabuTenure = 10;
    int maxIterations = 1000;

    std::deque<std::vector<int>> tabuList;

    std::srand(std::time(nullptr));

    Problem pocz_prob = NEH(problem);

    std::vector<int> obecnaKolejka(pocz_prob.getDane().size());
    for (int i = 0; i < problem.getDane().size(); ++i) {
        obecnaKolejka[i] = pocz_prob.getDane()[i].getNum();
    }

    setNajlepszaKolejka(obecnaKolejka);
    double obecnyCmax = obliczCmax(pocz_prob);

    najlepszaKolejka = obecnaKolejka;
    najlepszyCmax = obecnyCmax;

    int iterations = 0;

    while (iterations < maxIterations) {
        std::vector<int> bestCandidate = obecnaKolejka;
        double bestCandidateCmax = obecnyCmax;

        for (int i = 0; i < obecnaKolejka.size(); ++i) {
            for (int j = i + 1; j < obecnaKolejka.size(); ++j) {
                std::vector<int> candidate = obecnaKolejka;
                std::swap(candidate[i], candidate[j]);

                if (std::find(tabuList.begin(), tabuList.end(), candidate) != tabuList.end()) {
                    continue;
                }

                Problem pom_problem = pocz_prob;
                std::vector<Zadanie> tmp;
                for (int k = 0; k < candidate.size(); ++k) {
                    for (int l = 0; l < problem.getDane().size(); ++l) {
                        if (candidate[k] == problem.getDane()[l].getNum()) {
                            tmp.push_back(problem.getDane()[l]);
                        }
                    }
                }

                pom_problem.setDane(tmp);
                double candidateCmax = obliczCmax(pom_problem);
                // std::cout << candidateCmax << " - " << bestCandidateCmax << std::endl;

                if (candidateCmax < bestCandidateCmax) {
                    bestCandidate = candidate;
                    bestCandidateCmax = candidateCmax;
                }
            }
        }

        obecnaKolejka = bestCandidate;
        obecnyCmax = bestCandidateCmax;

        tabuList.push_back(obecnaKolejka);
        if (tabuList.size() > tabuTenure) {
            tabuList.pop_front();
        }

        if (obecnyCmax < najlepszyCmax) {
            najlepszaKolejka = obecnaKolejka;
            najlepszyCmax = obecnyCmax;
        }

        ++iterations;
    }

    setNajlepszaKolejka(najlepszaKolejka);
    setNajlepszyCmax(najlepszyCmax);
}