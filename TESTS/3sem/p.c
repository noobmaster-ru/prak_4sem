#include <sys/types.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>

// pr1 | pr2 > f.txt
int main(int argc, char *argv[]){
    int fd[2];

    pipe(fd);

    if (fork() == 0){
        close(fd[0]); // 0 - read , 1 - write
        dup2(fd[1],1);
        execlp(argv[1],argv[1],0);

    }

    if (fork() == 0){
        close(fd[1]);
        int file = open(argv[3],O_WRONLY | O_CREAT | O_TRUNC, 0666);
        dup2(file,1);
        dup2(fd[0],0);
        execlp(argv[2],argv[2],0);
    }
    wait(NULL);
    return 0;
}
