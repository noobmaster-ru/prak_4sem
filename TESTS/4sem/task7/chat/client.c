#include <sys/types.h> 
#include <sys/socket.h> 
#include <netinet/in.h> 
#include <netdb.h> 
#include <stdio.h> 
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>

extern int errno;

#define SIZE 256

void end_of_work(int sig){
    printf("\n");
    printf("end of work, good bye!\n");
    exit(EXIT_SUCCESS);
}
int main () {
    char c;
    int client_socket;
    FILE * fp;
    char hostname[64]; 
    struct hostent * hp; 
    struct sockaddr_in client_adr;
    /* в этом примере клиент и сервер выполняются на одном компьютере, но программа легко обобщается на случай разных компьютеров. 
    Для этого можно, например, использовать хост-имя не собственного компьютера, как ниже, а имя
    компьютера, на котором выполняется процесс-сервер */

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
    memcpy(&client_adr.sin_addr, hp->h_addr,hp->h_length);


    // пытаемся связаться с сервером:
    if ( connect ( client_socket, (struct sockaddr *)&client_adr, sizeof (client_adr)) < 0 ) { 
        perror ("client: connect");
        exit (1);
    }

    char* buffer_for_nickname = NULL;
    int size_buffer = 1;
    int index_in_buffer = 0; 

    
    printf("Enter your nickname: ");

    // send nickname
    c = getchar();
    while (c != '\0' && c != '\n' && c != ' '){
        buffer_for_nickname = realloc(buffer_for_nickname, size_buffer);
        buffer_for_nickname[index_in_buffer] = c;
        //printf("nickname[%d] = %c\n",index_in_buffer,c);
        index_in_buffer++;
        size_buffer++;
        c = getchar();
    }
    buffer_for_nickname[index_in_buffer] = '\0';
    //printf("nickname[%d] = %c\n",index_in_buffer,c);

    //printf("sizeof(nickname) = %d\n",strlen(buffer_for_nickname));
    //printf("size_buffer = %d\n",size_buffer);
    send(client_socket, buffer_for_nickname, strlen(buffer_for_nickname)+1,0);
    
    
    signal(SIGINT,end_of_work);
    while (1){
        // получаем от сервера никнейм того, кто вошёл в комнату
        ssize_t number_of_received_bytes;
        char nickname[SIZE];
        number_of_received_bytes = recv(client_socket, nickname, sizeof(nickname),0); 
        if (number_of_received_bytes < 0 ){
            perror("failed read from server");
            exit(EXIT_FAILURE);
        }
        else if (number_of_received_bytes == 0){
            // нет данных для чтения
            printf("no data from server");
            break;
        }  
        else{
            char * nickname_short = malloc(strlen(nickname)+1);
            strncpy(nickname_short,nickname,strlen(nickname)+1);
            
            // печатаем никнейм того, кто вошёл
            printf("new memver in the room : %s\n",nickname_short);
        }
    }
    close (client_socket);
    return 0;
}