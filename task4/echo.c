#include <stdio.h>
#include <string.h>
#include <stdlib.h>

char *buf; /* буфер для накопления текущего слова*/
int sizebuf; /* размер буфера текущего слова*/
int curbuf; /* индекс текущего символа в буфере*/

/* Функция nullbuf() присваивает переменной buf значение NULL, переменной sizebuf
(размер буфера) присваивает значение 0, переменной curbuf, указывающей очередную
свободную позицию в буфере, присваивает значение 0. */
void nullbuf(){
    buf=NULL;
    sizebuf=0;
    curbuf=0;
}

/* Функция addsym()добавляет очередной символ в буфер в позицию curbuf , после чего
переменная curbuf увеличивается на 1. Если буфер был пуст, то он создается. Если
размер буфера превышен, то он увеличивается на константу SIZE, заданную директивой
define. */
void addsym(char c){
    if (curbuf>sizebuf-1)
        buf=realloc(buf, sizebuf+=sizeof(char)); /* увеличиваем буфер при необходимости */
    buf[curbuf++] = c;
}

// печатаем слово с -E
void Print_E(int begin,int kol, char *argv[], int flag_n){
    for (int i = (begin+1); i < kol; i++){
        int j = 0;
        nullbuf();
        if (*(argv[i]+j) == '"'){
            j++;
            while (j < strlen(argv[i]) - 1){
                addsym(*(argv[i]+j));
                j++;
            }
        }
        else{
            while (j < strlen(argv[i])){
                addsym(*(argv[i]+j));
                j++;
            }
        }
        if (i != (kol-1)){
            printf("%s ",buf);
        }
        else{
            printf("%s",buf);
        }
        free(buf);
    }
    if (flag_n == 1)
        printf("\n");
}

// печатаем слово с -е
void Print_e(int begin, int kol, char *argv[],int flag_n){
    int count;
    for (int i = (begin+1); i < kol; i++){
        int j = 0;
        nullbuf();
        while (j < strlen(argv[i])){
            if (*(argv[i]+j) == '\\'){
                j++;
                switch (*(argv[i]+j)){
                        case '\\':
                            addsym('\\');
                            break;
                        case 'a':
                            addsym('\a');
                            break;
                        case 'b':
                            addsym('\b');
                            break;
                        case 'c':
                            printf("%s",buf);
                            free(buf);
                            exit(0);
                            break;
                        case 'e':
                            addsym('\e');
                            break;
                        case 'f':
                            addsym('\f');
                            break;
                        case 'n':
                            addsym('\n');
                            break;
                        case 'r':
                            addsym('\r');
                            break;
                        case 't':
                            addsym('\t');
                            break;
                        case 'v':
                            addsym('\v');
                            break;
                        case '0':
                            j++;
                            count = *(argv[i]+j) - '0';
                            j++;
                            count *= 8;
                            count += *(argv[i]+j) - '0';
                            j++;
                            count *= 8;
                            count += *(argv[i]+j) - '0';
                            addsym((char)count);
                            break;
                        case 'x':
                            j++;
                            count = *(argv[i]+j) - '0';
                            j++;
                            count *= 16;
                            count += *(argv[i]+j) - '0';
                            addsym((char)count);
                            break;
                        default:
                            addsym('\\');
                            addsym(*(argv[i]+j));
                            break;
                }
            }
            else{
                addsym(*(argv[i]+j));
            }
            j++;
        }
        if (i != (kol-1)){
            printf("%s ",buf);
        }
        else{
            printf("%s",buf);
        }
        free(buf);
    }
    if (flag_n == 1)
        printf("\n");
}

int main(int argc,char *argv[]){ 
    if (argc < 2){
        printf("\n");
        return 0;
    }

    int i = 1, 
        flag_n = 1,  
        flag_small_e = 0, 
        flag_big_e = 1, 
        number_of_descriptors = 0, 
        len_of_descriptors = 0,
        flag = 0;
    while ((*(argv[i]) == '-') && (i < argc) && (flag == 0)){
        switch (*(argv[i])){
            case '-':
                for (int pointer = 1; pointer < strlen(argv[i]); pointer++){
                    if (*(argv[i]+pointer) == 'n'){
                        flag_n = 0;
                    }
                    else if (*(argv[i]+pointer) == 'e'){
                        flag_small_e = 1;
                        flag_big_e = 0;
                    }
                    else if (*(argv[i]+pointer) == 'E'){
                        flag_big_e = 1;
                        flag_small_e = 0;
                    }
                }
                len_of_descriptors++;
                i++;
                break;
            default:
                flag = 1;
                break;
        }
    }

    if (flag_big_e == 1){
        Print_E(len_of_descriptors,argc,argv,flag_n);
    }
    else if (flag_small_e == 1){
        Print_e(len_of_descriptors,argc,argv,flag_n);
    }
    
    return 0;
}