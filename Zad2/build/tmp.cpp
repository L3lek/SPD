#include <iostream>
#include <fstream>
#include <string>

int main() {
    std::ifstream plik("dane7.txt"); // Nazwa pliku txt z danymi

    if (!plik) {
        std::cerr << "Nie można otworzyć pliku." << std::endl;
        return 1;
    }

    int suma = 0;
    int liczba;
    while (plik >> liczba) {
        suma += liczba;
    }

    plik.close();

    std::cout << "Suma liczb z pliku: " << suma << std::endl;

    return 0;
}