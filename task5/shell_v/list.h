
#define SIZE 16
int c; /*текущий символ */
char ** lst; /* список слов (в виде массива)*/
char * buf; /* буфер для накопления текущего слова*/ 
int sizebuf; /* размер буфера текущего слова*/
int sizelist; /* размер списка слов*/
int curbuf; /* индекс текущего символа в буфере*/ 
int curlist; /* индекс текущего слова в списке*/

void clearlist(char **lst);
void printlist();
void make_l();
