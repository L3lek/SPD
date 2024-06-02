#ifndef ZADANIE2_ZADANIE_H
#define ZADANIE2_ZADANIE_H
#include <string>
#include <vector>

class Zadanie {
private:
    int num;
    std::vector<double> tasks;

public:
    int getNum() const {return num;}
    void setNum(int num) {
        this->num = num;
    }
    std::vector<double> getTasks() const {return tasks;}
    void setTasks(std::vector<double> time) {
        Zadanie::tasks = time;
    }
    Zadanie(int num, std::vector<double> time) : num(num), tasks(time) {}
    void wyswietl();
    Zadanie();

    double pobierzSumeCzasow() const;

    double pobierzCzasNaPozycji(int pozycja) const;
};


#endif
