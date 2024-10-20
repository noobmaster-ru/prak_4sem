#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>
#include <signal.h>
#include <sys/wait.h>
#include "tree.h"
#include "list.h"
#include "exec.h"

void e_cd(char ** lst){
	int check;
	if (lst[1] != NULL){
		check =chdir(lst[1]);
	}
	else {
		check =chdir(getenv("HOME"));
	}
	if (check == -1){
		fprintf(stderr, "Error");

	}		
}


void execmd(tree t){
	int f1, f2;
	if (t->backgrnd==0){
		signal(SIGINT, SIG_DFL);
	}
	else{
		signal(SIGINT, SIG_IGN);
		
	}
	if (t->infile != NULL){
		if ((f1=open(t->infile, O_RDONLY)) == -1) {
			fprintf(stderr, "Error");
			exit(1);
		}
		dup2(f1, 0);
		close(f1);
	}

	if (t->outfile != NULL){
		if (t->doublegr == 0) {
			if  ((f2=open(t->outfile, O_WRONLY | O_CREAT | O_TRUNC, 0666)) == -1)  {
				fprintf(stderr, "Error");
				exit(1);

			}
		}
		else {
			if ((f2=open(t->outfile, O_WRONLY | O_CREAT | O_APPEND, 0666)) == -1)  {
				fprintf(stderr, "Error");
				exit(1);

			}
		}	
		dup2(f2, 1);
		close(f2);

	}
	if (t->backgrnd==1){
		int f3;
		if ((f3 = open("/dev/null", O_RDONLY)) == -1) {
			fprintf(stderr, "Error");
			exit(1);
		}
		dup2(f3, 0);
		close(f3);
		if (fork()==0){
			execvp(t->argv[0], t->argv);
			exit(0);
		}
		int status;
		wait(&status);
		if (WIFEXITED(status) && (WEXITSTATUS(status)==0)){
			count_b--;
		}	
	}	

	execvp(t->argv[0], t->argv);	
	exit(1);
	return;
}


void conv(tree t){
	int fd[2], in, out, next_in, i=1, j;
	tree g=t;
	pipe (fd);
	out=fd[1];
	next_in=fd[0];
	if (fork()==0){
		close(next_in);
		dup2(out,1);
		close(out);
		execmd(g);
		exit(-1);
	}
	in=next_in;
	g=g->pipe;
	while (g->pipe!=NULL){
		close(out);
		pipe(fd);
		out=fd[1];
		next_in=fd[0];
		if (fork()==0){
			close(next_in);
			dup2(in, 0);
			close(in);
			dup2(out, 1);
			close(out);
			execmd(g);
		}
		close(in);
		in=next_in;
		i++;
		g=g->pipe;
	}
	close(out);
	if (fork()==0){
		dup2(in,0);
		close(in);
		execmd(g);
	}
	close(in);
	for (j=1; j<=i; j++) wait(NULL);
}

void succmd(tree t){
	if (fork()==0){
		execmd(t);
	}
	int status;
	wait(&status);
	if (WIFEXITED(status) && (WEXITSTATUS(status)==0)){
		execmd(t->next);
	}	
}


void start(tree t){
	if (t->pipe != NULL){
		conv(t);
	} else if (t->next == NULL){
		if (fork()==0)
			execmd(t);
		wait(NULL);
	}
	else succmd(t);
	
}

