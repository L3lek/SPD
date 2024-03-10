#ifndef ZADANIE1_ZADANIE_H
#define ZADANIE1_ZADANIE_H


class Zadanie {
private:
    int num;
    double pj;
    double rj;
    double qj;
public:
    double getQj() const {return qj;}
    double getPj() const {return pj;}
    double getRj() const {return rj;}
    int getNum() const {return num;}

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
    static bool compare_qj(Zadanie z1, Zadanie z2);
    static bool compare_rj(Zadanie z1, Zadanie z2);
};


#endif
