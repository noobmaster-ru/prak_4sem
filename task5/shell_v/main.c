#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include "list.h"
#include "tree.h"
#include "exec.h"


void inv() {
	printf("%s", "\x1b[32m"); /* цвет изменяется на зеленый */
	char s[100]; /* ограничение: имя хоста и текущей директории не должно быть слишком длинным! */ 
	gethostname(s, 100);
	printf("%s@%s", getenv("USER"), s);
	printf("%s", "\x1B[31m"); /*  цвет изменяется на синий */
	getcwd(s, 100);
	printf(":%s$ ", s);
}

int main () {
	tree t;
	count_b=0;
	while (1==1){
		inv();
		fflush(0);
		make_l();
		if (lst != NULL){
			if (strcmp(lst[0], "exit")==0){
				clearlist(lst);
				break;
			} 
			else if (strcmp(lst[0], "cd")==0){
				e_cd(lst);
				clearlist(lst);
				continue;
			}
			else {
				t=build_tree();
				if (t==NULL) continue;
				start(t);
				printf("%d\n", count_b);
				cleartree(t);
				clearlist(lst);
				continue;
			}
		}
	}
}
