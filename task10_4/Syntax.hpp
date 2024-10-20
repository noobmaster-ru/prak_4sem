#ifndef SYNT
#define SYNT

#include "Lex.hpp"
#include "Poliz.hpp"

#include <stack>

using namespace std;

class Parser
{
    Lex curr_lex;
    type_of_lex c_type;
    int c_val;
    Scanner scan;
    stack<int>st_int;
    stack<type_of_lex>st_lex;
    
    void P();
    void SE();
    void IN();
    void UP();
    void DE();
    void CR();
    void DR();
    void CV();
    void WH();
    void E();  // обработка выражений
    void E1(); // обработка выражений с приоритетом
    void T();  // обработка выражений
    void F();  // обработка факторов
    void DS(); // обработка объявления структуры данных
    void dec(type_of_lex type);
    void check_id();
    void check_op();
    void check_not();
    void check_minus();
    void eq_type();
    void eq_bool();
    void check_id_in_read();
    void gl() // считывание лексемы
    {
        curr_lex = scan.get_lex ();
        c_type = curr_lex.get_type ();
        c_val = curr_lex.get_value ();
    }
public:
    Poliz poliz;
    Parser(const char *program):scan(program), poliz(1000){};
    void analyze();
};



#endif
