#include <stdio.h>
#include <stdlib.h>
#include "functions.h"

int main() {
    /*
    Or == |
    Umpersand == &
    Dott == ;
    Greater == >
    Less == <
    Left == (
    Right == )
    */
    typedef enum {Start, Word, Or , Or2 , Umpersand, Umpersand2 ,Dott , Greater, Greater2, 
        Less, Left, Right, Stop } vertex;
    vertex V=Start;
    c = getchar();
    null_list();
    int kol = 0;
    while(1 == 1 ){ 
        switch(V){
            case Start:
                if (c == EOF){
                    termlist();
                    printf(" kol = %d\n",kol);
                    printf("    Before sorting:  \n");
                    printlist();
                    V = Stop;
                }
                else{
                    nullbuf();
                    addsym();
                    switch (c){
                        case '|':
                            V = Or;
                            break;   
                        case '&':
                            V = Umpersand;
                            break;
                        case ';':
                            V = Dott;
                            break;
                        case '>':
                            V = Greater;
                            break;
                        case '<':
                            V = Less;
                            break;
                        case '(':
                            V = Left;
                            break;
                        case ')':
                            V = Right;
                            break;
                        default:
                            V = Word;
                            break;
                    }
                    c = getchar();
                }
            break;

            case Word:
                if(symset(c)) {
                    addsym();
                    c=getchar();
                }
                else{
                    V=Start;
                    kol++;
                    addword();
                }
            break;

            case Greater:
                if(c=='>') {
                    addsym();
                    c=getchar();
                    V=Greater2;
                }
                else {
                    V=Start;
                    kol++;
                    addword();
                }
            break;

            case Greater2:
                V=Start;
                kol++;
                addword();
            break;

            case Or:
                if(c=='|') {
                    addsym();
                    c=getchar();
                    V=Or2;
                }
                else {
                    V=Start;
                    kol++;
                    addword();
                }
            break;

            case Or2:
                V=Start;
                kol++;
                addword();
            break;
            

            case Umpersand:
                if(c=='&') {
                    addsym();
                    c=getchar();
                    V=Umpersand2;
                }
                else {
                    V=Start;
                    kol++;
                    addword();
                }
            break;

            case Umpersand2:
                V=Start;
                kol++;
                addword();
            break;

            case Dott:
                V = Start;
                kol++;
                addword();
            break;

            case Less:
                V = Start;
                kol++;
                addword();
            break;

            case Left:
                V = Start;
                kol++;
                addword();
            break;  

            case Right:
                V = Start;
                kol++;
                addword();
            break;

            case Stop:
                sortinglist();
                printf("    After sorting:   \n");
                printlist();
                clearlist();
                exit(0);
            break;
        }   
    }
}