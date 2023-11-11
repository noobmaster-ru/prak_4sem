#ifndef FUNCTIONS_H_
#define  FUNCTIONS_H_

extern int c; /*текущий символ */
extern char ** lst; /* список слов (в виде массива)*/
extern char * buf; /* буфер для накопления текущего слова*/
extern int sizebuf; /* размер буфера текущего слова*/
extern int sizelist; /* размер списка слов*/
extern int curbuf; /* индекс текущего символа в буфере*/
extern int curlist; /* индекс текущего слова в списке*/


void clearlist();
void null_list();
void termlist();
void nullbuf();
void addsym();
void addword();
void printlist();
int symset(int c);
void sortinglist();
#endif