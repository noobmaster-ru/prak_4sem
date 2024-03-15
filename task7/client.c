#include <sys/types.h> 
#include <sys/socket.h> 
#include <netinet/in.h> 
#include <netdb.h> 
#include <stdio.h> 
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <sys/wait.h>

extern int errno;



#define SIZE 256

void end(){
    printf("\n");
    printf("end of work, good bye!\n");
    exit(EXIT_SUCCESS);
}

int main () {
    char c;
    int client_socket;
    // FILE * fp;
    char hostname[64]; 
    struct hostent * hp; 
    struct sockaddr_in client_adr;
    

    // прежде всего получаем hostname собственной ЭВМ:
    gethostname (hostname, sizeof (hostname));

    // затем определяем сетевой номер своей машины:
    if ((hp = gethostbyname (hostname)) == NULL) { 
        fprintf (stderr, "%s: unknown host.\n", hostname);
        exit (1);
    }

    // получаем свой сокет-дескриптор:
    if ((client_socket= socket (AF_INET, SOCK_STREAM, 0)) < 0) { 
        perror ("client: socket");
        exit (1);
    }

    // создаем адрес, по которому будем связываться с сервером:
    client_adr.sin_family = AF_INET; 
    client_adr.sin_port = htons (1234);

    // копируем сетевой номер:
    memcpy(&client_adr.sin_addr, hp->h_addr_list[0], hp->h_length);
    free(hp);

    // пытаемся связаться с сервером:
    if ( connect ( client_socket, (struct sockaddr *)&client_adr, sizeof (client_adr)) < 0 ) { 
        perror ("client: connect");
        exit (1);
    }

    int end_of_work = 0;
    do{
        int len = 0; // изначально строка пуста
        int capacity = 1; // ёмкость контейнера динамической строки (1, так как точно будет '\n')
        char *command_from_user = (char*)malloc(sizeof(char)); // динамическая пустая строка

        char c = getchar(); // символ для чтения данных

        // читаем символы, пока не получим символ переноса строки (\n)
        while (c != '\n') {
            command_from_user[len++] = c; // заносим в строку новый символ

            // если реальный размер больше размера контейнера, то увеличим его размер
            capacity += 1; // увеличиваем ёмкость строки 
            command_from_user = (char*)realloc(command_from_user, capacity * sizeof(char)); // создаём новую строку с увеличенной ёмкостью  

            c = getchar(); // считываем следующий символ          
        }
        command_from_user[len] = '\n'; // завершаем строку символом конца строки

    
      
        send(client_socket, command_from_user, len+1 ,0);
        
        // /* ............................ */
        if (*(command_from_user+1) == '?'){
            ssize_t return_status;
            int received_int = 0;
            return_status = read(client_socket, &received_int, sizeof(received_int));
            if (return_status > 0) {
                printf("Number_increase_parameter = %d\n", ntohl(received_int));
                free(command_from_user);
            }
            else {
                perror("error received number form server");
                free(command_from_user);
                exit(EXIT_FAILURE);
            }
        }
        else if (*(command_from_user+1) == '+'){
            int len = 0; // изначально строка пуста
            int capacity = 1; // ёмкость контейнера динамической строки (1, так как точно будет '\0')
            char *answer_from_server = (char*) malloc(sizeof(char)); // динамическая пустая строка

            char oneByte;
            read(client_socket, &oneByte, 1);
            
            // читаем символы, пока не получим символ переноса строки (\n)
            while (oneByte != '\n') {
                answer_from_server[len++] = oneByte; // заносим в строку новый символ
                // если реальный размер больше размера контейнера, то увеличим его размер
                capacity += 1; // увеличиваем ёмкость строки 
                answer_from_server = (char*) realloc(answer_from_server, capacity * sizeof(char)); // создаём новую строку с увеличенной ёмкостью  
                read(client_socket, &oneByte, 1); // считываем следующий символ        
            }
            answer_from_server[len] = '\n'; // завершаем строку символом конца строки

            printf("answer from server = %s",answer_from_server);
            free(command_from_user);
        }
        else if (*(command_from_user+1) == '-'){
            end_of_work = 1;
            free(command_from_user);
            end();
        }
        else{
            ssize_t return_status;
            int received_int = 0;
            return_status = read(client_socket, &received_int, sizeof(received_int));
            if (return_status > 0) {
                printf("Number + Number_increase_parameter = %d\n", ntohl(received_int));
                free(command_from_user);
            }
            else {
                perror("error received number form server");
                free(command_from_user);
                exit(EXIT_FAILURE);
            }
        }
    
    }while (end_of_work != 1);
    close(client_socket);
    return 0;
}