#include <stdio.h>
#include <setjmp.h>

jmp_buf begin; // точка начал диалога с пользователем 
char curlex; // текущая лексема 
void getlex(void); // выделяет из текущего потока очереденую лексему 
int expr(void); // распознаёт выражение и вычисляет его значение 
int add(void); // распознаёт слагаемое и вычисляет его значение  
int mult(void); // распознаёт множитель и вычисляет его значение
void error(); // сообщает об ошибке и передаёт управление в начало функции main


int main(){
    int result;
    setjmp(begin);
    printf("==>");
    getlex();
    result = expr();
    if (curlex != '\n') error();
    printf("\n%d\n",result);
    return 0;
}


void getlex(){
    while ( (curlex = getchar() ) == ' ' );
}

void error(void){
    printf("\nОшибка!\n");
    while((getchar() != '\n'));
    longjmp(begin,1);
}

// вычисляет <выражение>:: =<слагаемое>{+/- <слагаемое>} 
int expr(){     
    int e=add();
    while (curlex == '^'){
        getlex();
        int count = expr();
        int i;
        for (i = 1; i < count; i++){
            e *= e;
        }
    }
    while (curlex == '+'){
        getlex();
        e += add();
    }
    while (curlex == '-'){
        getlex();
        e -= add();
    }
   return e;
}


// распознаёт слагаемое и вычисляет его значение  
int add(){ 
    int a = mult();
    while (curlex == '*'){
        getlex();
        a *= expr();
    }
    while (curlex == '/'){
        getlex();
        a /= mult();
    }
    return a;
}

// распознаёт множитель и вычисляет его значение
int mult(){
    int m;
    switch (curlex) {
    case '0' : case '1' : case '2' : case '3' : case '4' : case '5' :
    case '6' : case '7' : case '8' : case '9' : m = curlex - '0';
        break;
    case '(': 
            getlex();
            m = expr();
            if (curlex == ')') 
        break;
    default:
        error();
    }
    getlex();
    return m;
}
