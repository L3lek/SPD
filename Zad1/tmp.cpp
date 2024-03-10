#include <iostream>
#include <vector>
#include <algorithm>

class Zadanie {
private:
    int num;
    double pj;
    double rj;
    double qj;

public:
    double getQj() const { return qj; }
    double getPj() const { return pj; }
    double getRj() const { return rj; }
    int getNum() const { return num; }

    void setNum(int numer) {
        Zadanie::num = numer;
    }
    void setPj(double pj) {
        Zadanie::pj = pj;
    }
    void setRj(double rj) {
        Zadanie::rj = rj;
    }
    void setQj(double qj) {
        Zadanie::qj = qj;
    }

    Zadanie(int num, double pj, double rj, double qj);
    Zadanie();
    void generuj_wartosci();
    void wyswietl_zadanie();
    static double oblicz_czas(const std::vector<Zadanie>& zadania);
    static void generuj_permutacje(std::vector<Zadanie>& zadania, int start, double& najmniejszy_czas, std::vector<Zadanie>& aktualna_permutacja);
};

Zadanie::Zadanie(int num, double pj, double rj, double qj) : num(num), pj(pj), rj(rj), qj(qj) {}

Zadanie::Zadanie() {}

void Zadanie::generuj_wartosci() {
    // Implementacja generowania wartości (możesz dostosować do własnych potrzeb)
}

void Zadanie::wyswietl_zadanie() {
    // Implementacja wyświetlania informacji o zadaniu
    std::cout << "Zadanie " << num << ": pj=" << pj << ", rj=" << rj << ", qj=" << qj << std::endl;
}

double Zadanie::oblicz_czas(const std::vector<Zadanie>& zadania) {
    double najmniejszy_czas = 1000000;
    std::vector<Zadanie> aktualna_permutacja;

    generuj_permutacje(const_cast<std::vector<Zadanie>&>(zadania), 0, najmniejszy_czas, aktualna_permutacja);

    // Wypisz najmniejszy czas
    std::cout << "Najmniejszy czas: " << najmniejszy_czas << std::endl;

    // Wypisz kolejność zadań
    std::cout << "Kolejnosc wykonywania zadan: ";
    for (const auto& zadanie : aktualna_permutacja) {
        std::cout << zadanie.getNum() << " ";
    }
    std::cout << std::endl;

    return najmniejszy_czas;
}

void Zadanie::generuj_permutacje(std::vector<Zadanie>& zadania, int start, double& najmniejszy_czas, std::vector<Zadanie>& aktualna_permutacja) {
    if (start == zadania.size()) {
        double czas = 0.0;
        double c_j_minus_1 = zadania[0].getRj();

        for (const auto& zadanie : zadania) {
            c_j_minus_1 = std::max(c_j_minus_1, zadanie.getRj());
            czas += std::max(c_j_minus_1 + zadanie.getPj() + zadanie.getQj(), c_j_minus_1);
            c_j_minus_1 += zadanie.getPj();
        }

        if (czas < najmniejszy_czas) {
            najmniejszy_czas = czas;
            aktualna_permutacja = zadania;
        }
        return;
    }

    for (int i = start; i < zadania.size(); ++i) {
        std::swap(zadania[start], zadania[i]);
        generuj_permutacje(zadania, start + 1, najmniejszy_czas, aktualna_permutacja);
        std::swap(zadania[start], zadania[i]);
    }
}

int main() {
    // Przykładowe zadania
    std::vector<Zadanie> zadania = {
        Zadanie(1, 0, 3, 7),
        Zadanie(2, 2, 2, 10),
        Zadanie(3, 4, 5, 3),
        // Dodaj więcej zadań według potrzeb
    };

    // Wywołaj funkcję oblicz_czas
    Zadanie::oblicz_czas(zadania);

    return 0;
}
