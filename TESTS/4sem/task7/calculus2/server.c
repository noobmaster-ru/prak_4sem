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

void end_of_work(int sig){
    printf("\n");
    if (sig == SIGINT){
        printf("end of the work");
        exit(EXIT_SUCCESS);
    }
}

int main (int argc, char* argv[]){
    int server_socketfd = Socket(AF_INET,SOCK_STREAM,0);
    struct sockaddr_in adr = {0};
    adr.sin_family = AF_INET;
    adr.sin_port = htons(34543);
    Bind(server_socketfd,(struct sockaddr *) &adr,sizeof(adr));
    Listen(server_socketfd,5);

    int end_of_work = 0,
        number_increase_parameter = 1,
        global_increase_parameter = 0;
    int number_one = 0, number_two = 0;
    int list_of_sock_desctiptors[2] = {0,0};

    signal(SIGINT,end_of_work);
    signal(SIGTSTP,end_of_work);
    signal(SIGTERM,end_of_work);
    while (end_of_work == 0){
        socklen_t adrlen = sizeof(adr);
        int new_socket_fd = Accept(server_socketfd, (struct sockaddr *) &adr, &adrlen);
        while (end_of_work == 0){
            ssize_t number_of_received_bytes;
            char buf[256];
            number_of_received_bytes = recv(new_socket_fd, buf, sizeof(buf), 0);
            if (buf[0] == '\\' ){
                // set number_increase_parameter
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
                    write(new_socket_fd,"Ok", 2);
                }
                // what is number_increase_parameter ?
                else if (buf[1] == '?'){
                    // printf("buf[1] = %c\n",buf[1]);
                    // printf("number increase parametr = %d\n",number_increase_parameter);
                    // printf("strlen = %lu\n",strlen(buf));
                    int converted_number = htonl(number_increase_parameter);
                    write(new_socket_fd, &converted_number,sizeof(converted_number));
                }
                // end of the work.
                else if (buf[1] == '-'){
                    //printf("end");
                    end_of_work = 1;
                }
            }
            // set global_increase_parameter
            else if (buf[0] == '+'){
                int index_in_buffer = 0, 
                    number_in_client_request = 0; 
                for (int i = 1; i < strlen(buf)-1; i++){
                    number_in_client_request *= 10;
                    number_in_client_request += buf[i] - '0';
                }

                global_increase_parameter = number_in_client_request;
                printf("global increase parameter = %d\n",global_increase_parameter);

                int converted_number = htonl(global_increase_parameter);
                write(new_socket_fd, &converted_number, sizeof(converted_number));

                // wait two numbers from clients
                ssize_t number_of_received_bytes_one, number_of_received_bytes_two ;
                char buf_number_one[256], buf_number_two[256];
                number_of_received_bytes_one = recv(new_socket_fd, buf_number_one, sizeof(buf_number_one), 0);
                number_of_received_bytes_two = recv(new_socket_fd, buf_number_two, sizeof(buf_number_two), 0);

                int number_in_client_request_one = 0, 
                    number_in_client_request_two = 0; 
                for (int i = 0; i < strlen(buf_number_one)-1; i++){
                    number_in_client_request_one *= 10;
                    number_in_client_request_one += buf_number_one[i] - '0';
                    //printf("number = %d\n",number_in_client_request);
                }
                for (int i = 0; i < strlen(buf_number_two)-1; i++){
                    number_in_client_request_two *= 10;
                    number_in_client_request_two += buf_number_two[i] - '0';
                    //printf("number = %d\n",number_in_client_request);
                }
                printf("number_one = %d , number_two = %d\n",number_in_client_request_one,number_in_client_request_two);
                int result = number_in_client_request_one + number_in_client_request_two + global_increase_parameter;
                converted_number = htonl(result);
                write(new_socket_fd, &converted_number,sizeof(converted_number));
            }
            // only number
            else{
                //printf("number of received bytes = %zd\n",number_of_received_bytes);
                //printf("buf = %s",buf);
                int number_in_client_request = 0; 
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
                // printf("number from client = %d\n",number_in_client_request);
                // if (number_one == 0){
                //     number_one = number_in_client_request;
                //     list_of_sock_desctiptors[0] = new_socket_fd;
                // }
                // else if (number_two == 0){
                //     number_two = number_in_client_request;
                //     list_of_sock_desctiptors[1] = new_socket_fd;
                //     int result = number_one + number_two + global_increase_parameter;
                //     int converted_number = htonl(result);
                //     // write(list_of_sock_desctiptors[0], &converted_number,sizeof(converted_number));
                //     // write(list_of_sock_desctiptors[1], &converted_number,sizeof(converted_number));
                //     write(new_socket_fd, &converted_number,sizeof(converted_number));
                //     // write(new_socket_fd, &converted_number,sizeof(converted_number));
                //     number_one = 0;
                //     number_two = 0;
                //     list_of_sock_desctiptors[0] = 0;
                //     list_of_sock_desctiptors[1] = 0;
                // }

                // printf("list[0] = %d, number_one = %d\n",list_of_sock_desctiptors[0],number_one);
                // printf("list[1] = %d, number_two = %d\n",list_of_sock_desctiptors[1],number_two);

                //printf("number in client request = %d\n",number_in_client_request);
                if (global_increase_parameter == 0){
                    number_in_client_request += number_increase_parameter;
                }
                else{
                    number_in_client_request += global_increase_parameter;
                }
                int converted_number = htonl(number_in_client_request);
                write(new_socket_fd, &converted_number,sizeof(converted_number));
            }
            // write(STDOUT_FILENO, buf, number_of_received_bytes);
        } 
        //printf("end of work = %d\n",end_of_work);
        close(new_socket_fd);
    }
    close(server_socketfd);
    return 0;
}