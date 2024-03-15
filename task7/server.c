#include <sys/types.h> 
#include <sys/socket.h> 
#include <netinet/in.h> 
#include <netdb.h> 
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <sys/select.h>
#include <sys/wait.h>
#include <signal.h>

#define SIZE 256


void end_of_work(int sig){
    printf("\n");
    if (sig == SIGINT){
        printf("end of work, bye.\n");
        exit(EXIT_SUCCESS);
    }
}


int main () {
    char c;
    fd_set active_set, read_set;
    int server_listen_socket, new_socket_for_service_client; 
    int i;
    socklen_t fromlen;
    char hostname[1024];
    struct hostent *hp;
    struct sockaddr_in server_adr, client_adr;

    signal(SIGINT,end_of_work);

    // получаем хост-имя собственной ЭВМ:
    gethostname (hostname, sizeof (hostname));

    // определяем сетевой номер своей машины:
    if ((hp = gethostbyname (hostname)) == NULL) { 
        fprintf (stderr, "%s: unknown host.\n", hostname); 
        exit (EXIT_FAILURE);
    }

    // получаем свой сокет-дескриптор:
    if ((server_listen_socket = socket (AF_INET, SOCK_STREAM, 0)) < 0) { 
        perror ("client: socket");
        exit (EXIT_FAILURE);
    }

    // создаем адрес, который свяжется с сокетом:
    server_adr.sin_family = AF_INET; 
    server_adr.sin_port = htons (1234);


    // копируем сетевой номер:
    memcpy ( &server_adr.sin_addr, hp->h_addr_list[0], hp->h_length);
    free(hp);

    // связываем адрес с сокетом
    if ( bind ( server_listen_socket, (struct sockaddr *)&server_adr, sizeof (server_adr)) < 0 ){ 
        perror ("server: bind");
        exit (EXIT_FAILURE);
    }

    // слушаем запросы на сокет
    if(listen(server_listen_socket,5)<0){ 
        perror ("server: listen"); 
        exit (EXIT_FAILURE);
    }


    while (1){

        socklen_t adrlen = sizeof(server_adr);
        int new_socket_fd = accept(server_listen_socket, (struct sockaddr *) &server_adr, &adrlen); 
        int number_increase_parameter = 1;
        // сын обслуживает запрос
        if (fork() == 0){
            int end_of_work = 0;
            do{
                int len = 0; // изначально строка пуста
                int capacity = 1; // ёмкость контейнера динамической строки (1, так как точно будет '\0')
                char *command_from_client =  (char*)malloc(sizeof(char)); // динамическая пустая строка


                char oneByte;
                read(new_socket_fd, &oneByte, 1);
                // читаем символы, пока не получим символ переноса строки (\n)
                while (oneByte != '\n') {
                    command_from_client[len++] = oneByte; // заносим в строку новый символ

                    // если реальный размер больше размера контейнера, то увеличим его размер
                    capacity += 1; // увеличиваем ёмкость строки 
                    command_from_client = (char*)realloc(command_from_client, capacity * sizeof(char)); // создаём новую строку с увеличенной ёмкостью  

                    read(new_socket_fd, &oneByte, 1);    
                }

                command_from_client[len] = '\n'; // завершаем строку символом конца строки
                

                if (*(command_from_client+0) == '\\' ){
                    if (*(command_from_client+1) == '+'){
                        int index_in_buffer = 0, 
                            number_in_client_request = 0; 
                        for (int i = 2; i < len; i++){
                            number_in_client_request *= 10;
                            number_in_client_request += (*(command_from_client+i) - '0');
                        }
                        number_increase_parameter = number_in_client_request;
                        send (new_socket_fd, "Ok\n", 3, 0);
                        free(command_from_client);
                    }
                    else if (*(command_from_client+1) == '?'){
                        int converted_number = htonl(number_increase_parameter);
                        write(new_socket_fd, &converted_number,sizeof(converted_number));
                        free(command_from_client);
                    }
                    else if (*(command_from_client+1) == '-'){
                        printf("process-client was killed\n");

                        end_of_work = 1;
                        free(command_from_client);
                    }
                }
                else{
                    int index_in_buffer = 0, number_in_client_request = 0; 
                    for (int i = 0; i < len; i++){
                        number_in_client_request *= 10;
                        number_in_client_request += (*(command_from_client+i) - '0');
                       
                    }
                    number_in_client_request += number_increase_parameter;
                    int converted_number = htonl(number_in_client_request);
                    write(new_socket_fd, &converted_number,sizeof(converted_number));
                    free(command_from_client);
                }
                command_from_client = NULL;
            } while (end_of_work == 0); 
        }
        wait(NULL); 
        close(new_socket_fd);
    }

    close(server_listen_socket);
    return 0;
}
