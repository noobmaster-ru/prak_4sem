#ifndef POLIZ
#define POLIZ

#include "Lex.hpp"

#include <stack>
#include <vector>

using namespace std;

class Poliz
{
    Lex *p;    //массив лексем
    int sizen; //размер
    int free;  //индекс первого свободного элемента
public:
    int count = 0;
    Poliz(int maxxx)
    {
        sizen = maxxx;
        p = new Lex[sizen];
        free = 0;
    }

    ~Poliz() {delete []p;}

    int size() {return sizen;}
    void put_lex(Lex l)
    {
        p[free]=l;
        free++;
    }

    void put_lex(Lex l, int place) {p[place] = l;}
    void blank() {++free;}
    int get_free() {return free;}
    Lex& operator[] (int index);
    void operator = (Poliz& A);
    void print();
};

#endif
