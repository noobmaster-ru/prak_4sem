#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>

#define N 5

void eat(int i){
    printf("ph %d eat\n", i);
    sleep(4);
}

void think(int i){
    printf("ph %d think\n", i);
    sleep(4);
}

void up(int* sem_id, int i){
    struct sembuf semaphore[2];

    semaphore[0].sem_num = i;
    semaphore[0].sem_op = -1; // захватываем левую вилку
    semaphore[0].sem_flg = SEM_UNDO;
    
    semaphore[1].sem_num = (i + 1) % N;
    semaphore[1].sem_op = -1; // захватываем правую вилку
    semaphore[1].sem_flg = SEM_UNDO;
    
    semop(*sem_id, semaphore, 2);
}

void down(int* sem_id, int i){
    struct sembuf semaphore[2];
    
    semaphore[0].sem_num = i;
    semaphore[0].sem_op = 1; // освобождаем левую вилку
    semaphore[0].sem_flg = SEM_UNDO;
    
    semaphore[1].sem_num = (i + 1) % N;
    semaphore[1].sem_op = 1; // освобождаем правую вилку
    semaphore[1].sem_flg = SEM_UNDO;
    
    semop(*sem_id, semaphore, 2);
}



void philosopher(int* sem_id, int i) {
    while (1){
        think(i);
        printf("ph %d hungry\n", i);
        up(sem_id, i);
        eat(i);
        down(sem_id, i);
    }
}

int main(void){
    int sem_id = semget(IPC_PRIVATE, N, IPC_CREAT | 0666);

    for (int i = 1; i <= N; i++)
        semctl(sem_id, i, SETVAL, 1);


    for (int i = 1; i <= N; i++){
        if (fork() == 0){
            philosopher(&sem_id, i);
            exit(0);
        }
    }

    for (int i = 0; i < N; i++)
        wait(NULL);
    semctl(sem_id, 0, IPC_RMID, 0);
    return 0;
}
