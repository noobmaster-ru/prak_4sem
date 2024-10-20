#include "Poliz.hpp"

using namespace std;

//перегрузка оператора [] для ПОЛИЗа (его элементам)
Lex& Poliz::operator[](int index)
{
    if(index > size())
        throw "POLIZ: out of array range";
    else
        return p[index];
};

//перегрузка оператора = для копирования
void Poliz::operator=(Poliz& A){
    sizen = A.size();
    delete[] p;
    p = new Lex[sizen];
    free = A.get_free();
    for(int i = 0; i < sizen; i++){
        p[i] = A.p[i];
    }
}

//печать
void Poliz::print() {
    for(int i = 0; i < free; ++i)
        if(p[i].get_type() == POLIZ_SENTENCE)
            cout << endl;
        else
            cout << p[i]; // debug
};
