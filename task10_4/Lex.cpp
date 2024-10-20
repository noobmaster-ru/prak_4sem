#include "Lex.hpp"

using namespace std;

/*
TW - таблица служебных слов
TD - таблица ограничителей
TID - таблица идентификаторов анализируемой программы
*/

/*
Перегруженный оператор выводакоторый позволяет выводить объекты типа Lex в поток вывода.
Он выводит лексему в формате (тип_лексемы, значение_лексемы, "имя_лексемы").
*/

ostream& operator << (ostream & s, Lex l)
{
    s << '(' << l.t_lex << ',' << l.v_lex << ",\"" << l.name_of_lex << "\");" ;
    return s;
}

string Scanner:: TW[] = { "NULL",
    "AND", "SELECT", "LOGIC", "INSERT", "UPDATE",
    "DELETE", "FALSE", "LONG", "NOT", "OR", "CREATE",
    "DROP", "TRUE", "WHERE", "TABLE", "INTO", "FROM",
    "SET", "IN", "ALL", "TEXT", "EXIT", "#"
};

string Scanner:: TD[] = { "NULL",
    "\'", ",", "(", ")", "=", "<", ">",
    "+", "-", "*", "/", "<=", "!=", ">="
};

vector <Ident> TID;

/*
добавляет строку buf в таблицу идентификаторов, если она там ещё не присутствует, и возвращает её индекс.
*/

int put(const string & buf)
{
    vector<Ident>::iterator k;

    k = find(TID.begin(), TID.end(), buf);

    if(k != TID.end())
        return k - TID.begin();
        
    TID.push_back(Ident(buf));
    return TID.size() - 1;
}
//Читает лексему и решает в каком состоянии находится Scanner в зависимости от текущей лексемы
Lex Scanner::get_lex()
{
    enum state{
        H,       // Начальное состояние
        IDENT,   // Идентификатор (переменная)
        NUMB,    // Число
        COM,     // Комментарий
        ALE,     // < > = <= >=
        NEQ,     // !=
        LETTER   // "string"
    };
    state CS = H;
    string buf;
    int d, j, sign_flag = 1;
    
    do{
        gc();
        switch(CS)
        {
            case H:
                if(c == ' ' || c == '\n' || c == '\r' || c == '\t') {}
                else if (isalpha(c) || c == '{' || c == '}')
                {
                    buf.push_back(c);
                    CS = IDENT;
                }
                else if(isdigit(c))
                {
                    d = c - '0';
                    CS = NUMB;
                }
                else if (c == '\'')
                {
                    CS = LETTER;
                }
                else if(c == '-')
                {
                    sign_flag = -1;
                    j = look(buf, TD, TDlen);
                    counts[(int) LEX_MINUS]++;
                    return Lex(LEX_MINUS, j, "-");
                    break;
                }
                else if(c == '#')
                    CS = COM;
                
                else if(c == '=' || c == '<' || c == '>')
                {
                    buf.push_back(c);
                    CS = ALE;
                }
                else if ( c == '!' ) {
                    buf.push_back(c);
                    CS = NEQ;
                }
                else
                {
                    buf.push_back(c);
                    if((j = look( buf, TD, TDlen)))
                    {
                        counts[(int) (j - 1 + (int) LEX_EXIT)]++;
                        return Lex((type_of_lex) (j - 1 + (int) LEX_EXIT), j, buf);
                    }

                    else throw c;
                }
                break;

            case IDENT:
                if(isalpha(c) || isdigit(c) || c == '_')
                {
                    buf.push_back(c);
                }
                else
                {
                    ungetc(c, fp);

                    if((j = look(buf, TW, TWlen)))
                    {
                        counts[j]++;
                        return Lex ((type_of_lex) j , j, buf );
                    }
                    else
                    {
                        j = put(buf);
                        counts[(int) LEX_ID]++;
                        return Lex(LEX_ID, j, buf);
                    }
                }
                break;

            case NUMB:
                if(isdigit(c)){
                    d = d * 10 + (c - '0');
                }
                else{
                    ungetc(c, fp);
                    d *= sign_flag;
                    sign_flag = 1;
                    counts[(int) LEX_NUM]++;
                    return Lex(LEX_NUM, d, "NUM");
                }
                break;
            case COM:
                if(c == '\n'){
                    CS = H;
                }
                else if(c == '#') throw c;
                break;
            case ALE:
                if(c == '='){
                    buf.push_back(c);
                    j = look(buf, TD, TDlen);
                    counts[(int) (j - 1 + (int) LEX_EXIT)]++;
                    return Lex((type_of_lex) (j - 1 + (int) LEX_EXIT), j, buf );
                }
                else {
                    ungetc(c, fp);
                    j = look (buf, TD, TDlen);
                    counts[(int) ( j - 1 + (int) LEX_EXIT)]++;
                    return Lex ((type_of_lex) ( j - 1 + (int) LEX_EXIT), j, buf );
                }
                break;
            case NEQ:
                if(c == '='){
                    buf.push_back(c);
                    j = look(buf, TD, TDlen);
                    counts[(int) LEX_NEQ]++;
                    return Lex(LEX_NEQ, j, buf);
                }
                else throw '!';
                break;
            case LETTER:
                if(c == '\''){
                    CS = H;
                    j = put(buf);
                    counts[(int) LEX_LETTER]++;
                    return Lex((type_of_lex) (LEX_LETTER), j , buf);
                }
                else {
                    buf.push_back(c);
                }
                break;
        }
    }
    while (true);
};
