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


// https://rsdn.org/article/unix/sockets.xml  - читать !!!!!
// https://rsdn.org/article/unix/sockets.xml  - читать !!!!!
// https://rsdn.org/article/unix/sockets.xml  - читать !!!!!
// https://rsdn.org/article/unix/sockets.xml  - читать !!!!!
// https://rsdn.org/article/unix/sockets.xml  - читать !!!!!
// https://rsdn.org/article/unix/sockets.xml  - читать !!!!!
// https://rsdn.org/article/unix/sockets.xml  - читать !!!!!
// https://rsdn.org/article/unix/sockets.xml  - читать !!!!!
// https://rsdn.org/article/unix/sockets.xml  - читать !!!!!
// https://rsdn.org/article/unix/sockets.xml  - читать !!!!!
// https://rsdn.org/article/unix/sockets.xml  - читать !!!!!
// https://rsdn.org/article/unix/sockets.xml  - читать !!!!!
// https://rsdn.org/article/unix/sockets.xml  - читать !!!!!
// https://rsdn.org/article/unix/sockets.xml  - читать !!!!!
// https://rsdn.org/article/unix/sockets.xml  - читать !!!!!
// https://rsdn.org/article/unix/sockets.xml  - читать !!!!!

extern int errno;

#define SIZE 256

typedef struct node *link_struct; // pointer to list node
typedef char* elemtype;    /*  list element type */
typedef struct node
{                  /* list node type */
    elemtype elem; /* element type */
    link_struct next;     /* pointer to the next node */
} node;

typedef link_struct list; /* list type (pointer to the first node) */

list list_of_nicknames = NULL, pointer;

void end_of_work(int sig){
    printf("\n");
    pointer = list_of_nicknames;
    while (pointer != NULL){
        printf("%s ",pointer->elem);
        pointer = pointer->next;
    }
    printf("\n");
    if (sig == SIGINT){
        exit(EXIT_SUCCESS);
    }
}

int main () {
    char c;
    fd_set active_set, read_set;
    int server_listen_socket, new_socket_for_service_client; 
    int i;
    socklen_t fromlen;
    FILE * fp;
    char hostname[1024];
    struct hostent *hp;
    struct sockaddr_in server_adr, client_adr;



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
    memcpy ( &server_adr.sin_addr, hp->h_addr, hp->h_length);

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
    
    // обнуляем множество active_set
    FD_ZERO(&active_set);
    // заполняем в active_set сокет связанный с сервером => будет установлено 1 в месте, где слушающий сервер
    FD_SET(server_listen_socket, &active_set);

    signal(SIGINT,end_of_work);
    // бесконечный цикл работы сервера 
    while (1){
        // проверяем не появились ли данные в одном из сокетов 
        read_set = active_set;
        if (select(FD_SETSIZE,&read_set,NULL,NULL,0) < 0){
            perror("server select error");
            exit(EXIT_FAILURE);
        }

        // данные появились, проверяем на каком сокете
        for (i = 0; i < FD_SETSIZE; i++){
            if (FD_ISSET(i,&read_set)){
                if (i == server_listen_socket){
                    // пришёл запрос на соединение 
                    // для каждого нового клиента создаётся свой отдельный сокет
                    if((new_socket_for_service_client = accept ( server_listen_socket, (struct sockaddr *)&client_adr, &fromlen)) < 0){
                        perror ("server: accept");
                        exit (EXIT_FAILURE); 
                    }
                    FD_SET(new_socket_for_service_client,&active_set);
                }
                else{
                    // пришли данные в уже существующем соединении 

                    // получаем никнейм от клиента
                    ssize_t number_of_received_bytes;
                    char nickname[SIZE];
                    number_of_received_bytes = recv(new_socket_for_service_client, nickname, sizeof(nickname), 0);
                    
                    // заносим клиента в список
                    char * nickname_short = malloc(strlen(nickname)+1);
                    strncpy(nickname_short,nickname,strlen(nickname)+1);
                    if (list_of_nicknames == NULL){
                        list_of_nicknames = (link_struct)malloc(sizeof(node));
                        list_of_nicknames->elem = nickname_short;
                        pointer = list_of_nicknames;
                    }
                    else {
                        pointer->next = (link_struct)malloc(sizeof(node));
                        pointer = pointer->next;
                        pointer->elem = nickname_short;
                        pointer->next = NULL;
                    }

                    send(new_socket_for_service_client, nickname_short, strlen(nickname_short)+1,0);
                    printf("nickname = %s\n",nickname_short);
                    close(new_socket_for_service_client);
                    FD_CLR(i,&active_set);
                }
            }
        }
    }
    
    close(server_listen_socket);
    return 0;
}