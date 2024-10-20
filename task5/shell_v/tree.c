#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>
#include "tree.h"
#include "list.h"

tree make_cmd(){
	tree t;
	t = calloc(1, sizeof(struct cmd_inf));
	t -> argv = NULL;
	t -> infile = NULL;
	t -> outfile = NULL;
	t -> doublegr = 0;
	t -> backgrnd = 0;
	t -> pipe = NULL;
	t -> next = NULL;
	return t;
}

int wset(char *w){ 
	return (strcmp(w, "|")!=0) &&
	       (strcmp(w, "&")!=0)  &&
	       (strcmp(w, "<")!=0) && 
	       (strcmp(w, ">")!=0) &&
	       (strcmp(w, ">>")!=0) ;
}


void make_bgrnd(tree t){
	while (t != NULL){
		t->backgrnd = 1;
		count_b ++;
		t = t->pipe;
	}
}

void add_arg(tree t){
	
	if (t->argv == NULL){
		t->argv = calloc(1, sizeof(* t->argv));
	}
	int i=0;	
	while (t->argv[i]) i++;

	
	t->argv[i]=calloc(strlen(curw)+1, sizeof(char));
	strncpy(t->argv[i++], curw, strlen(curw)+1);
	t->argv = realloc(t->argv, ((i+1) * sizeof(*t->argv)));
	t->argv[i]=NULL;
}

void cleartree(tree t){
	if (t==NULL) return;
	clearlist(t->argv);
	free(t->infile);
	free(t->outfile);
	cleartree(t->next);
	cleartree(t->pipe);
	free(t);
	t=NULL;
}
///////////////////////////////////
void make_shift(int n){
    while(n--)
        putc(' ', stderr);
}

void print_argv(char **p, int shift){
    char **q=p;
    if(p!=NULL){
        while(*p!=NULL){
             make_shift(shift);
             fprintf(stderr, "argv[%d]=%s\n",(int) (p-q), *p);
             p++;
        }
    }
}

void print_tree(tree t, int shift){
    char **p;
    if(t==NULL)
        return;
    p=t->argv;
    if(p!=NULL)
        print_argv(p, shift);
    else{
        make_shift(shift);
        fprintf(stderr, "psubshell\n");
    }
    make_shift(shift);
    if(t->infile==NULL)
        fprintf(stderr, "infile=NULL\n");
    else
        fprintf(stderr, "infile=%s\n", t->infile);
    make_shift(shift);
    if(t->outfile==NULL)
        fprintf(stderr, "outfile=NULL\n");
    else
        fprintf(stderr, "outfile=%s\n", t->outfile);
    make_shift(shift);
    fprintf(stderr, "append=%d\n", t->doublegr);
    make_shift(shift);
    fprintf(stderr, "background=%d\n", t->backgrnd);
    make_shift(shift);
    make_shift(shift);
    if(t->pipe==NULL)
        fprintf(stderr, "pipe=NULL \n");
    else{
        fprintf(stderr, "pipe---> \n");
        print_tree(t->pipe, shift+5);
    }
    make_shift(shift);
    if(t->next==NULL)
        fprintf(stderr, "next=NULL \n");
    else{
        fprintf(stderr, "next---> \n");
        print_tree(t->next, shift+5);
    }
}

////////////////////////////////////
tree build_tree(){
	tree s;
	tree c;
	tree p;

	typedef enum { begin, conv, conv1, in, in1, out, out1, 
		end, backgrnd, Err, succ, nextback
		
	} vertex; 
	vertex V=begin;
	ind=0;
	if (lst != NULL){
		while(1==1) switch(V){
			case begin:
				s=c=make_cmd();
				curw=lst[ind];				
				add_arg(c);
				ind++;
				curw=lst[ind];
				if (curw != NULL){
					p=c;
					V=conv;
				}
				else
					V=end;
			break;

			case conv:
				if (strcmp(curw, "|")==0){
					V=conv1;
				}
				else if (strcmp(curw, "<")==0) {
					V=in;
				}
				else if (strcmp(curw, "&")==0) {
					V=backgrnd;
				}
				else if ((strcmp(curw, ">")==0)||(strcmp(curw, ">>")==0)) {
					V=out;
				}
				else if (strcmp(curw, "<")==0) {
					V=in;
				}
				else if (strcmp(curw, "&&")==0){
					ind++;
					curw = lst[ind];
					if ((curw != NULL)&&(wset(curw))){
						V=succ;
					} else
						V=Err;
				}
				else {
					add_arg(c);
					ind++;
					curw = lst[ind];
					if (curw == NULL){
						V=end;
					}
				}

			break;
		
			case succ:
				c=make_cmd();
				p->next = c;
				add_arg(c);
				ind++;
				curw=lst[ind];
				if (curw == NULL){
					V=end;
				}	
				else {
					V=conv;
				}
			break;
			

			case conv1:
				c=make_cmd();
				
				p->pipe = c;
				p=c;
				ind++;
				curw = lst[ind];
				if ((curw!=NULL) && (wset(curw)))
					V=conv;
				
				else V = Err;
			break;

			case in:
				ind++;
				curw=lst[ind];
				if ((strcmp(curw, ">>")==0) || (strcmp(curw, ">")==0)) V=out;
				else if ((curw!=NULL) && (wset(curw))){
					V=in1;
				}
				else V=Err;
			break;

			case in1:
				len_f=strlen(curw)+1;
				c->infile = calloc(len_f, sizeof(char));
				
				strncpy(c->infile, curw, len_f);
				
				ind++;
				curw=lst[ind];
				if (curw!=NULL){
					V=conv;
				} else V=end;
			break;

			case out:
				if (strcmp(curw, ">>")==0){
					c->doublegr = 1;
				}
				ind++;
				curw=lst[ind];
				if ((curw!=NULL) && (wset(curw))){
					V=out1;
				}
				else V=Err;

			break;

			case out1:
				len_f=strlen(curw)+1;
				c->outfile = calloc(len_f, sizeof(char));
				
				strncpy(c->outfile, curw, len_f);
				
				ind++;
				curw=lst[ind];
				if (curw!=NULL){
					V=conv;
				} else V=end;

			break;

			case backgrnd:
				make_bgrnd(s);
				ind++;
				curw=lst[ind];
				if (curw == NULL){
					V=end;
				} else if (wset(curw)==0) V=Err;
				else V=nextback;
				
			break;

			case nextback:
				c=make_cmd();

				p->next = c;
				s=p=c;
				add_arg(c);

				ind++;
				curw=lst[ind];
				
				if (curw==NULL) V=end;
				else V=conv;
			break;

			case end:
				return s;
			break;

			case Err:
				clearlist(lst);
				cleartree(s);
				fprintf(stderr, "Error");
				exit(0);
			break;
		}
	} 
	return NULL;
}