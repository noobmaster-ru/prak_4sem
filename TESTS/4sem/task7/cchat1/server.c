#include <sys/types.h> 
#include <sys/socket.h> 
#include <stdio.h> 
#include <stdlib.h>
#include <sys/un.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>
#include <signal.h>


int Socket(int domain, int type, int protocol){
    int res = socket(domain, type, protocol);
    if (res == -1){
        perror("socket failed");
        exit(EXIT_FAILURE);
    }
    return res;
}

void Bind(int socket, const struct sockaddr *address, socklen_t address_len){
    int res = bind(socket, address, address_len);
    if (res == -1){
        perror("bind failed");
        exit(EXIT_FAILURE);
    }
}

void Listen(int socket, int backlog){
    int res = listen(socket,backlog);
    if (res == -1){
        perror("listen failed");
        exit(EXIT_FAILURE);
    }
}

int Accept(int socket, struct sockaddr *restrict address, socklen_t *restrict address_len){
    int res = accept(socket, address, address_len);
    if (res == -1){
        perror("accept failed ");
        exit(EXIT_FAILURE);
    }
    return res;
}


int main (int argc, char* argv[]){
    int server_socketfd = Socket(AF_INET,SOCK_STREAM,0);
    struct sockaddr_in adr = {0};
    adr.sin_family = AF_INET;
    adr.sin_port = htons(1234);
    Bind(server_socketfd,(struct sockaddr *) &adr,sizeof(adr));
    Listen(server_socketfd,5);


    int end_of_work = 0;
    while (end_of_work == 0){
        socklen_t adrlen = sizeof(adr);
        int new_socket_fd = Accept(server_socketfd, (struct sockaddr *) &adr, &adrlen); 

        while (end_of_work == 0){
            ssize_t number_of_received_bytes;
            char nickname[256];
            number_of_received_bytes = recv(new_socket_fd, nickname, sizeof(nickname), 0);
            
            
            printf("nuckname = %s\n",nickname);


            // if (curbuf > sizebuf-1)
            //     buf = realloc(buf, sizebuf += sizeof(char));
            // //buf[curbuf++] = nickname[i];

            // buf = realloc(buf,sizebuf = curbuf);
            // if (curlist > sizelist-1)
            //     lst=realloc(lst, (sizelist+=1)*sizeof(*lst)); /* увеличиваем массив под список при необходимости */
            // lst[curlist++] = buf;
            // // printf("nickname = %s",buf);
            // // printf("sizelist = %d\n",sizelist);
            // for (i=0; i<sizelist; i++)
            //     printf("%s ",lst[i]);

         
        } 
        //printf("end of work = %d\n",end_of_work);
        close(new_socket_fd);
    }
    close(server_socketfd);
    return 0;
}