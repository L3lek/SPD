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
        //        case 4: {
//            auto start = std::chrono::high_resolution_clock::now();
//            this->FNEH(dane);
//            this->wyswietl();
//            // this->wyswietl_kolejnosc();
//            auto end = std::chrono::high_resolution_clock::now();
//            auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();
//            std::cout << "Czas wykonania metody NEH: " << duration << " ms\n";
//            break;
//        }
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
            this->thresholdAcceptingCmax(dane, 10, 5000);
            this->wyswietl();
            //this->wyswietl_kolejnosc();
            auto end = std::chrono::high_resolution_clock::now();
            auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();
            std::cout << "Czas wykonania symulowanego wyżarzania: " << duration << " ms\n";
            break;
        }
        case 8: {
            auto start = std::chrono::high_resolution_clock::now();
            najlepszyCmax = variableNeighborhoodSearchCmax(dane, 10000, 3);
            this->wyswietl();
            //this->wyswietl_kolejnosc();
            auto end = std::chrono::high_resolution_clock::now();
            auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();
            std::cout << "Czas wykonania symulowanego wyżarzania: " << duration << " ms\n";
            break;
        }
        
        default:
            std::cout << "Błędna opcja\n";
            break;
    }
}

void Rozwiazanie::NEH(Problem& problem) {
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
    // Parametry algorytmu
    double temperaturaPoczatkowa = 10000;
    double temperaturaKoncowa = 1;
    double wspolczynnikChlodzenia = 0.999;

    // Zainicjuj losowy generator
    std::srand(std::time(nullptr));

    // Zainicjuj rozwiązanie początkowe
    std::vector<int> obecnaKolejka(problem.getDane().size());
    for (int i = 0; i < problem.getDane().size(); ++i) {
        obecnaKolejka[i] = problem.getDane()[i].getNum();
    }

    setNajlepszaKolejka(obecnaKolejka);
    double obecnyCmax = obliczCmax(problem);
    najlepszaKolejka = obecnaKolejka;
    najlepszyCmax = obecnyCmax;

    double temperatura = temperaturaPoczatkowa;

    while (temperatura > temperaturaKoncowa) {
        // Wygeneruj nowe rozwiązanie przez zamianę dwóch losowych zadań
        std::vector<int> nowaKolejka = obecnaKolejka;
        int i = std::rand() % nowaKolejka.size();
        int j = std::rand() % nowaKolejka.size();
        std::swap(nowaKolejka[i], nowaKolejka[j]);

        // Oblicz wartość Cmax dla nowego rozwiązania
        setNajlepszaKolejka(nowaKolejka);
        double nowyCmax = obliczCmax(problem);

        // Akceptuj nowe rozwiązanie na podstawie prawdopodobieństwa
        if (nowyCmax < obecnyCmax || std::exp((obecnyCmax - nowyCmax) / temperatura) > ((double) std::rand() / RAND_MAX)) {
            obecnaKolejka = nowaKolejka;
            obecnyCmax = nowyCmax;

            // Aktualizuj najlepsze rozwiązanie, jeśli jest lepsze
            if (nowyCmax < najlepszyCmax) {
                najlepszaKolejka = nowaKolejka;
                najlepszyCmax = nowyCmax;
            }
        }

        // Obniż temperaturę
        temperatura *= wspolczynnikChlodzenia;
    }

    // Ustaw najlepsze znalezione rozwiązanie
    setNajlepszaKolejka(najlepszaKolejka);
    setNajlepszyCmax(najlepszyCmax);
}

double Rozwiazanie::thresholdAcceptingCmax(Problem& problem, double initialThreshold, int maxIterations) {
    int iloscZadan = problem.getN();
    int iloscMaszyn = problem.getM();
    std::vector<Zadanie> zadania = problem.getDane();


    this->najlepszaKolejka.clear();
    najlepszyCmax = std::numeric_limits<double>::max();  // Initialize najlepszyCmax to a large value

    // Start with initial solution
    double currentCmax = obliczCmax(problem);

    // Initialize threshold and iteration counter
    double threshold = initialThreshold;
    int iterations = 0;

    // Threshold Accepting loop
    while (iterations < maxIterations && threshold > 0.1) {  // Example stopping conditions
        // Generate a neighboring solution (perturb current solution)
        perturbSolution(problem);

        // Compute Cmax for the perturbed solution
        double newCmax = obliczCmax(problem);

        // Acceptance criteria: Replace current solution if better
        if (newCmax < currentCmax) {
            currentCmax = newCmax;
            for(int i=0;i<problem.getDane().size();i++){
                najlepszaKolejka.push_back(problem.getDane()[i].getNum());
            }
            najlepszyCmax = currentCmax;  // Update najlepszyCmax
        } else {
            // Calculate acceptance probability
            double acceptanceProbability = exp(-(newCmax - currentCmax) / threshold);

            // Randomly decide whether to accept the worse solution
            double randValue = static_cast<double>(rand()) / RAND_MAX;
            if (randValue < acceptanceProbability) {
                currentCmax = newCmax;
                for(int i=0;i<problem.getDane().size();i++){
                    najlepszaKolejka.push_back(problem.getDane()[i].getNum());
                }
                najlepszyCmax = currentCmax;  // Update najlepszyCmax
            }
        }

        // Decrease threshold (example: reduce it by a fixed amount)
        threshold -= 0.0001;
        iterations++;
    }

    return najlepszyCmax;
}

void Rozwiazanie::perturbSolution(Problem& problem) {
    // Example perturbation method: swap two random tasks
    std::vector<Zadanie> tasks = problem.getDane();
    int n = tasks.size();

    int idx1 = rand() % n;
    int idx2 = rand() % n;

    if (idx1 != idx2) {
        std::swap(tasks[idx1], tasks[idx2]);
    }
}

double Rozwiazanie::variableNeighborhoodSearchCmax(Problem& problem, int maxIterations, int neighborhoodSize) {
    int iloscZadan = problem.getN();
    int iloscMaszyn = problem.getM();
    std::vector<Zadanie> zadania = problem.getDane();

    // Initial solution and best found solution
    std::vector<Zadanie> najlepszeRozwiazanie = zadania;
    double najlepszyCmax = obliczCmax(problem);

    // Current solution and current Cmax
    std::vector<Zadanie> aktualneRozwiazanie = zadania;
    double aktualnyCmax = najlepszyCmax;

    int iteracje = 0;

    while (iteracje < maxIterations) {
        for (int i = 0; i < neighborhoodSize; ++i) {
            int idx1 = rand() % iloscZadan;
            int idx2 = rand() % iloscZadan;

            if (idx1 != idx2) {
                std::swap(aktualneRozwiazanie[idx1], aktualneRozwiazanie[idx2]);
            }
        }

        double nowyCmax = obliczCmax(problem);

        if (nowyCmax < aktualnyCmax) {
            aktualnyCmax = nowyCmax;
            najlepszeRozwiazanie = aktualneRozwiazanie;
        } else {
            double acceptanceProbability = exp(-(nowyCmax - aktualnyCmax) / iteracje);

            double randValue = static_cast<double>(rand()) / RAND_MAX;
            if (randValue < acceptanceProbability) {
                aktualnyCmax = nowyCmax;
                najlepszeRozwiazanie = aktualneRozwiazanie; 
            }
        }

        iteracje++;
    }

    problem.setDane(najlepszeRozwiazanie);

    return najlepszyCmax;
}
