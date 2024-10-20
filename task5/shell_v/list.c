#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <pwd.h>
#include "list.h"


void clearlist(char **lst){ 
	int i;
	sizelist=0;
	curlist=0;
	if (lst==NULL) return;
	for (i=0; lst[i]!=NULL; i++)
		free(lst[i]);
    	free(lst);
	lst=NULL; 
}

static void null_list(){ 
	sizelist=0;
	curlist=0;
	lst=NULL; 
}

static void termlist(){
	if (lst==NULL) return; 
	if (curlist>sizelist-1)
	lst=realloc(lst,(sizelist+1)*sizeof(*lst));
    	lst[curlist]=NULL;
   	 /*выравниваем используемую под список память точно по размеру списка*/
    	lst=realloc(lst,(sizelist=curlist+1)*sizeof(*lst));
}

static void nullbuf(){ 
	buf=NULL;
	sizebuf=0;
	curbuf=0;
}

static void addsym(){
	if (curbuf>sizebuf-1)
        	buf=realloc(buf, sizebuf+=SIZE); /* увеличиваем буфер при
                                            необходимости */
   	buf[curbuf++]=c;
}

static void addword(){
	if (curbuf>sizebuf-1)
        	buf=realloc(buf, sizebuf+=1); /* для записи ’\0’ увеличиваем буфер при   необходимости  */
   	 buf[curbuf++]='\0';
   	 /*выравниваем используемую память точно по размеру слова*/
    	buf=realloc(buf,sizebuf=curbuf);
	if (curlist>sizelist-1)
		lst=realloc(lst, (sizelist+=SIZE)*sizeof(*lst)); /* увеличиваем
															массив под список при необходимости */ 
    	lst[curlist++]=buf;
}

void printlist(){ 
	int i;
	if (lst==NULL) return;
	for (i=0; i<sizelist-1; i++)
       		printf("%s ",lst[i]);
	printf("\n");
}




static int symset(int c){ 
	return c!='\n' &&
	       c!=' ' &&
	       c!='\t' && 
	       c!='>' &&
	       c!='|' &&
	       c!='&' &&
	       c!=')' &&
	       c!='(' &&
	       c!='<' &&
	       c!=';' &&
	       c!=',' &&
	       c!='\"' &&
	       c!='#' &&
	       c!='\\' &&
		c!= EOF ;
}

static char s[12];
static int ind=0;

static void getsym(){
	if (s[ind]=='\0'){
		ind=0;
		s[0]='\0';
		fscanf(stdin, "%10[^\n]", s); 
		c=getchar();
		if (c!=EOF){
			int i;
			for (i=0; s[i]!='\0';i++)
				;
			s[i]=c;
			s[i+1]='\0';
			
		}
		else
			return;
	}
	
	c=s[ind];
	ind++;
}




extern void make_l() {
	typedef enum {Start, Word, Greater, Greater2, 
		Stop, amber, skob, htag, pip,  slash, dol, cav,
		Err
	} vertex; 
	vertex V=Start;

	
	char *dollar;

	null_list();
	getsym();
	
	while(1==1) switch(V){
 		case Start:
			if(c==' '||c=='\t'){
				getsym();
			}
		    else if (c==EOF){
    			termlist();
    			clearlist(lst);
    			V=Stop;
			}
			else if (c=='\n') {
    			termlist();
    			V=Stop;		
			}
			else if (c== '$'){
				nullbuf();				
				V = dol;
				getsym();
			}
			else if (c== '\"'){
				nullbuf();
				V = cav;
				getsym();				
			}
			else if (c== '#'){
				nullbuf();
				V = htag;
				getsym();	
			}
			else if (c== '\\'){
				nullbuf();
				V =slash;
				getsym();	
			}else{
				nullbuf();
				addsym();
				if (c=='&') {
					V= amber;
				}
				else if (c=='|') {
					V= pip;
				}
				else if ((c=='(')||(c==')')) {
					V=skob;
				}
				else {
					V= ((c=='>')||(c==';')||(c==',')||(c=='<'))? Greater: Word;
				}
				getsym();
			}
		break;
	
		case Word:
			if(symset(c)) { 
				addsym();
				getsym();
			}
			else { 
				V=Start;
				addword();
		    } 
		break;
	
		case Greater: 
			if(c=='>') {
				addsym();
				getsym();
				V=Greater2;
			}
			else {
				V=Start;
				addword();
			}
		break;

		case amber: 
			if(c=='&') {
				addsym();
				getsym();
				V=Greater2;
			}
			else {
				V=Start;
				addword();
			}

		break;

		case pip: 
			if(c=='|') {
				addsym();
				getsym();
				V=Greater2;
			}
			else {
				V=Start;
				addword();
			}

		break;

		case Greater2:
			V=Start;
			addword();
		break;


		case htag: /* пропускаем все после */
			if ((c=='\n')||(c==EOF)){
				V=Start;
			}
			else getsym();
		break;
		
		case slash:  /*пропускаем спецсимволы */
			if (symset(c)){
				V=Word;
			}
			else{
				if ((c=='\n')||(c==EOF)){
					V=Start;
					addword();
				}
				else {
					V=Start;
					addsym();
					getsym();
				}
			}
		break;

		case cav:
			if (c=='\"'){
				V=Start;
				addword();
				getsym();
			} else {
				addsym();
				getsym();
			}
		break;

		case skob: 
			V=Start;
			addword();

		break;

		case dol:
			if (c=='H'){ /* $HOME */
				getsym();
				if (c!='O'){
					V=Err;
					break;
				}
				getsym();
				if (c!='M') {
					V=Err;
					break;

				}
				getsym();
				if (c!='E') {
					V=Err;
					break;
				}
				dollar = getenv("HOME");
				while (*dollar){
					c = *dollar;
					addsym();
					dollar++;
				}
				addword();
				getsym();
				V=Start;

			}
			else if (c=='S'){ /* $SHELL */ 
				getsym();
				if (c!='H'){
					V=Err;
					break;
				}
				getsym();
				if (c!='E') {
					V=Err;
					break;
				}
				getsym();
				if (c!='L') {
					V=Err;
					break;
				}
				getsym();
				if (c!='L') {
					V=Err;
					break;
				}
				dollar = getenv("SHELL");
				while (*dollar){
					c = *dollar;
					addsym();
					dollar++;
				}
				addword();
				getsym();
				V=Start;
			}
			else if (c=='U'){ /* $USER */
				getsym();
				if (c!='S') {
					V=Err;
					break;
				}
				getsym();
				if (c!='E') {
					V=Err;
					break;
				}
				getsym();
				if (c!='R') {
					V=Err;
					break;
				}
				
				dollar = getlogin();
				while (*dollar){
					c = *dollar;
					addsym();
					dollar++;
				}
				addword();
				getsym();
				V=Start;


			}
			else if (c=='E'){ /* $EUID */
				getsym();
				if (c!='U') {
					V=Err;
					break;
				}
				getsym();
				if (c!='I') {
					V=Err;
					break;
				}
				getsym();
				if (c!='D') {
					V=Err;
					break;
				}
				uid_t ui = geteuid();
				struct passwd *pw;
				pw = getpwuid(ui);
				sprintf(dollar, "%d",  pw->pw_uid);
				while (*dollar){
					c = *dollar;
					addsym();
					dollar++;
				}
				addword();
				getsym();
				V=Start;

				
			}
			else { /* вывод ошибки */
				V=Err;
			}
		break;

		case Err: 
			nullbuf();
			fprintf(stderr, "Error\n");
			clearlist(lst);
			exit(0);
		break; 

		
		case Stop:
			nullbuf();
			return;
		break;

	}
}