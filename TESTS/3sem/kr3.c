// (pr1 | pr2) || pr3 > f4
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/wait.h>

int main(int argc, char *argv[]) {
    int pipefd[2];
    pid_t pid1, pid2, pid3;
    int status1, status2, status3;
    int fd4;
    pipe(pipefd);
    if (fork() == 0){
        close(pipefd[0]); // 0 - read
        dup2(pipefd[1], STDOUT_FILENO);
        close(pipefd[1]);
        execlp(argv[1], argv[1], NULL);
    }
    if (fork() == 0) {
        close(pipefd[1]);
        dup2(pipefd[0], STDIN_FILENO);
        close(pipefd[0]);
        execlp(argv[2], argv[2], NULL);
    }
    close(pipefd[0]);
    close(pipefd[1]);
    waitpid(pid1, &status1, 0);
    waitpid(pid2, &status2, 0);
    if (WIFEXITED(status1) && WIFEXITED(status2) 
        && WEXITSTATUS(status1) == 0 && WEXITSTATUS(status2) == 0){
        fd4 = open("f4", O_WRONLY | O_CREAT | O_TRUNC, 0666);
        if (fork() == 0){
            dup2(argv[4], STDOUT_FILENO);
            execlp(argv[3], argv[3], NULL);
        }  
        waitpid(pid3, &status3, 0);
    }
    else{
        printf("pr1 or pr2 failed\n");
        exit(EXIT_FAILURE);
    }
    // (pr1 | pr2) || pr3 > f4
    return 0;
}
