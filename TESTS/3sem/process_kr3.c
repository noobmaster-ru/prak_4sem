#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <stdlib.h>
#include <stdio.h>

int main(int argc, char **argv){
    //  (pr1 || pr2) | pr3
 	int fd[2];

    pipe(fd);

    if (fork() == 0){
        int status;
        pid_t pid;
		// int fd[2];

   		// pipe(fd);
        if ((pid = fork()) == 0){
            dup2(fd[1], 1);
            close(fd[1]);
            close(fd[0]);
            execlp(argv[1], argv[1], 0);
        }
        wait(&status);
        close(fd[0]);

        if(!(WIFEXITED(status) && WEXITSTATUS(status) == 0)){
            if (fork() == 0){
                dup2(fd[1], 1);
                close(fd[1]);
                close(fd[0]);
                execlp(argv[2], argv[2], 0);
                _exit(0);
            }
            wait(NULL);
        }
        close(fd[1]);
        _exit(0);
    }

    if (fork() == 0)
    {
        dup2(fd[0], 0);
        close(fd[0]);
        close(fd[1]);

        execlp(argv[3], argv[3], 0);
        _exit(0);
    }
    close(fd[0]);
    close(fd[1]);
    wait(NULL);
    wait(NULL);
}