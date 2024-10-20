#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/wait.h>

// pr1 arg1 < f.dat;  pr2 | pr3 >> f.res

int main(int argc, char *argv[]){

    if (fork() == 0){
        int file = open(argv[3],O_RDONLY);
        dup2(file,0);
        execlp(argv[1],argv[1],argv[2],0);
    }
    wait(NULL);
    int fd[2];
    pipe(fd);

    if (fork() == 0){
        close(fd[0]);
        dup2(fd[1],1);
        execlp(argv[4],argv[4],0);
    }
    //printf("%s \n\n",argv[6]);
    if (fork()==0){
        int file = open(argv[6], O_WRONLY | O_CREAT | O_APPEND | O_TRUNC,0666);
        dup2(file,1);
        dup2(fd[0],0);
        execlp(argv[5],argv[5],0);
    }

    return 0;
}