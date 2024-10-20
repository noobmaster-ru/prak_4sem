#include "Lex.hpp"
#include "Syntax.hpp"
#include "Execute.hpp"
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <fstream>

using namespace std;

int main(){
    try{
        int y = 3;
        cout << "What part do you want to test? (1 - lexical, 2 - syntax, 3 - execute)" << endl;
        cin >> y;
        if(y == 1)
        {
            Scanner scan("test.txt");
            Lex H = scan.get_lex();
            cout << H << endl;
            while(H.get_type() != LEX_EXIT)
            {
                H = scan.get_lex();
                cout << H << endl;
            }
            
            int maxelem = 0;
            int maxind = 0;
            
            for (int i = 0; i < 41; i++)
                if (maxelem < scan.counts[i])
                {
                    maxind = i;
                    maxelem = scan.counts[i];
                }

            for (int i = 0; i < 41; i++)
                cout << scan.counts[i] << ' ';
            
            cout << endl;
            cout << "The most popular: " << maxind << endl;
        }
        
        else if (y == 2)
        {
            Parser Par("test.txt");
            Par.analyze();
            Par.poliz.print();
            cout << "Number of type TEXT in table: " << Par.poliz.count << endl;
        }

        else if(y == 3)
        {
            Interpretator I("test.txt");
            I.interpretation();
        }
           
        return 0;
    }
    catch(char c)
    {
        cout << endl << "unexpected symbol " << c << endl;
        return 1;
    }
    catch(Lex l)
    {
        cout << endl << "unexpected lexeme " << l << endl;
        return 1;
    }
    catch(const char *source)
    {
        cout << source << endl;
        return 1;
    }
    catch(...)
    {
        cout << endl << "Unknown error" << endl;
        return 1;
    }
    return 0;
}
