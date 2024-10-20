#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>

#define N 5

void eat(int i){
    printf("Philosopher %d eating\n", i+1);
    sleep(5);
}

void think(int i){
    printf("Philosopher %d thinking\n", i+1);
    sleep(5);
}

void up(int* sem_id, int i){
    struct sembuf sops[2];

    sops[0].sem_num = i;
    sops[0].sem_op = -1; // захватываем левую вилку
    sops[0].sem_flg = SEM_UNDO;
    
    sops[1].sem_num = (i + 1) % N;
    sops[1].sem_op = -1; // захватываем правую вилку
    sops[1].sem_flg = SEM_UNDO;
    
    semop(*sem_id, sops, 2);
}

void down(int* sem_id, int i){
    struct sembuf sops[2];
    
    sops[0].sem_num = i;
    sops[0].sem_op = 1; // освобождаем левую вилку
    sops[0].sem_flg = SEM_UNDO;
    
    sops[1].sem_num = (i + 1) % N;
    sops[1].sem_op = 1; // освобождаем правую вилку
    sops[1].sem_flg = SEM_UNDO;
    
    semop(*sem_id, sops, 2);
}



void philosopher(int* sem_id, int ph_number) {
    while (1){
        think(ph_number);
        printf("Philosopher %d hungry\n\n", ph_number+1);
        up(sem_id, ph_number);
        eat(ph_number);
        down(sem_id, ph_number);
    }
}

int main(){
    int sem_id = semget(IPC_PRIVATE, N, IPC_CREAT | 0666);
    int waiting_end = 0;

    for (int i = 0; i < N; i++){
        semctl(sem_id, i, SETVAL, 1);
    }   

    for (int number_philosopher = 0; number_philosopher < N; number_philosopher++){
        if (fork() == 0){
            philosopher(&sem_id, number_philosopher);
            exit(waiting_end);
        }
    }

    for (int i = 0; i < N; i++){
        wait(&waiting_end);
    }
    semctl(sem_id, 0, IPC_RMID, 0);
    
    return 0;
}
