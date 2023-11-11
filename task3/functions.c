#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SIZE 16

int c; /*текущий символ */
char ** lst; /* список слов (в виде массива)*/
char * buf; /* буфер для накопления текущего слова*/
int sizebuf; /* размер буфера текущего слова*/
int sizelist; /* размер списка слов*/
int curbuf; /* индекс текущего символа в буфере*/
int curlist; /* индекс текущего слова в списке*/


/* Функция clearlist() освобождает память, занимаемую списком (если он не пуст), и
делает список пустым. Переменную sizelist (размер списка) обнуляет, переменную
curlist, указывающую очередную свободную позицию в списке, тоже обнуляет. */
void clearlist(){
    int i;
    sizelist=0;
    curlist=0;
    if (lst==NULL) return;
    for (i=0; lst[i]!=NULL; i++)
        free(lst[i]);
    free(lst);
    lst=NULL;
}


/* Функция null_list() присваивает переменной lst, представляющую список, значение
NULL (пустой список). Переменную sizelist (размер списка) обнуляет, переменную
curlist, указывающую очередную свободную позицию в списке, тоже обнуляет */
void null_list(){
    sizelist=0;
    curlist=0;
    lst=NULL;
}

/* Функция termlist() завершает список, добавляя NULL в позицию curlist и
обрезает память, занимаемую списком, до точного размера. */
void termlist(){
    if (lst==NULL) return;
    if (curlist>sizelist-1)
        lst = realloc(lst,(sizelist+1)*sizeof(*lst));
    lst[curlist]=NULL;
    /*выравниваем используемую под список память точно по размеру списка*/
    lst = realloc(lst,(sizelist = curlist+1)*sizeof(*lst));
}

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
void addsym(){
    if (curbuf>sizebuf-1)
        buf=realloc(buf, sizebuf+=SIZE); /* увеличиваем буфер при необходимости */
    buf[curbuf++] = c;
}

/* Функция addword() завершает текущее слово в буфере, добавляя ’\0’ в позицию curbuf
(увеличив, если нужно, буфер), и обрезает память, занимаемую словом, до точного
размера; затем добавляет слово в список в позицию curlist, после чего значение
curlist увеличивается на 1. Если список был пуст, то он создается. Если размер списка
превышен, то он увеличивается на константу SIZE. */
void addword(){
    if (curbuf>sizebuf-1)
        buf=realloc(buf, sizebuf+=1); /* для записи ’\0’ увеличиваем буфер при необходимости */
    buf[curbuf++]='\0';

    /*выравниваем используемую память точно по размеру слова*/
    buf=realloc(buf,sizebuf=curbuf);
    if (curlist>sizelist-1)
        lst=realloc(lst, (sizelist+=SIZE)*sizeof(*lst)); /* увеличиваем массив под список при необходимости */
    lst[curlist++]=buf;
}


// print list 
void printlist(){
    int i;
    if (lst==NULL) return;

    for (i=0; i<sizelist-1; i++)
        printf("%s\n",lst[i]);
}

/* любой символ, кроме пробела, табуляции, перевода строки и специальных
символов (>, >>), и не конец файла (EOF). */
int symset(int c){
    return c != '|' &&
        c != '&' && 
        c != ';'&& 
        c != '>'&& 
        c != '<' &&
        c != '(' &&
        c != ')' &&
        c != EOF ;
}

void sortinglist(){
    for (int i = 0; i < sizelist-2; i++){
        for (int j = i+1; j < sizelist-1; j++){
            if (strcmp(lst[i],lst[j]) > 0 ){
                char *buf1;
                buf1 = lst[i];
                lst[i] = lst[j];
                lst[j] = buf1;
            }
        }
    }
}