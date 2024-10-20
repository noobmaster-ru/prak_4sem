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
    adr.sin_port = htons(34543);
    Bind(server_socketfd,(struct sockaddr *) &adr,sizeof(adr));
    Listen(server_socketfd,5);

    int end_of_work = 0,
        number_increase_parameter = 1;
    while (end_of_work == 0){
        socklen_t adrlen = sizeof(adr);
        int new_socket_fd = Accept(server_socketfd, (struct sockaddr *) &adr, &adrlen); 
        // сын обслуживает запрос
        pid_t pid;
        if ((pid = fork()) == 0){
            do{
                ssize_t number_of_received_bytes;
                char buf[256];
                number_of_received_bytes = recv(new_socket_fd, buf, sizeof(buf), 0);
                if (buf[0] == '\\' ){
                    if (buf[1] == '+'){
                        int index_in_buffer = 0, 
                            number_in_client_request = 0; 
                        //printf("strlen = %lu\n",strlen(buf));
                        // while (buf[index_in_buffer] != '\0' && buf[index_in_buffer] != '\n' ){
                        //     number_in_client_request *= 10;
                        //     number_in_client_request += buf[index_in_buffer] - '0';
                        //     index_in_buffer++;
                        // }
                        for (int i = 2; i < strlen(buf)-1; i++){
                            number_in_client_request *= 10;
                            number_in_client_request += buf[i] - '0';
                        }
                        //printf("number in client request = %d\n",number_in_client_request);
                        number_increase_parameter = number_in_client_request;
                        send (new_socket_fd,"Ok", 2, 0);
                    }
                    else if (buf[1] == '?'){
                        // printf("buf[1] = %c\n",buf[1]);
                        // printf("number increase parametr = %d\n",number_increase_parameter);
                        // printf("strlen = %lu\n",strlen(buf));
                        int converted_number = htonl(number_increase_parameter);
                        write(new_socket_fd, &converted_number,sizeof(converted_number));
                    }
                    else if (buf[1] == '-'){
                        //printf("end");
                        end_of_work = 1;
                        break;
                    }
                }
                else{
                    //printf("number of received bytes = %zd\n",number_of_received_bytes);
                    //printf("buf = %s",buf);
                    int index_in_buffer = 0, number_in_client_request = 0; 
                    // while (buf[index_in_buffer] != '\0' && buf[index_in_buffer] != '\n' ){
                    //     number_in_client_request *= 10;
                    //     number_in_client_request += buf[index_in_buffer] - '0';
                    //     index_in_buffer++;
                    // }
                    for (int i = 0; i < strlen(buf)-1; i++){
                        number_in_client_request *= 10;
                        number_in_client_request += buf[i] - '0';
                        //printf("number = %d\n",number_in_client_request);
                    }
                    //printf("number in client request = %d\n",number_in_client_request);
                    number_in_client_request += number_increase_parameter;
                    int converted_number = htonl(number_in_client_request);
                    write(new_socket_fd, &converted_number,sizeof(converted_number));
                }
                // write(STDOUT_FILENO, buf, number_of_received_bytes);
            } while (end_of_work == 0); 
            //printf("end of work = %d\n",end_of_work);
        }
        wait(NULL); 
        close(new_socket_fd);
    }

    close(server_socketfd);
    return 0;
}