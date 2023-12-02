#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

int main(){
    char *dir;
    int n = 1;
    dir = (char*)malloc(sizeof(char)*n);
    while (getcwd(dir,n) == NULL){
        n++;
        dir = (char*)realloc(dir,n);
    }
    
    printf("%s\n", dir);
    return 0; 
}