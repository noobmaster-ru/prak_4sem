#ifndef EXEC
#define EXEC

//#include "Lex.hpp"
#include "Syntax.hpp"
#include "Table.hpp"

#include <stack>
#include <vector>
#include <string.h>
#include <iostream>

using namespace std;

class Interpretator
{
    Lex pc_el;        //текущая лексема ПОЛИЗа
    int c_poliz;      //индекс текущего элемента ПОЛИЗа
    string c_table;   //текущая таблица
    THandle table;    //обработчик таблицы символов
    int size;
    Parser pars;

    stack<long> args;
    stack<string> str_args;

    void expression(Poliz& poliz); //вычисление выражений
    vector<bool> where();          //вычисление where
    void execute();                //выполнение команд
    void gp()                      //получение следующего элемента ПОЛИЗа
    {
        c_poliz++;
        pc_el = pars.poliz[c_poliz];
        //cout << pc_el;
    }
public:
    Interpretator(const char *program):pars(program){
        c_poliz = 0;
    };
    void interpretation();
};



#endif
