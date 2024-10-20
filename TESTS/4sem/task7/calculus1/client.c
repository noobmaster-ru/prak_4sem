#include <sys/types.h> 
#include <sys/socket.h> 
#include <stdio.h> 
#include <stdlib.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/un.h>
#include <unistd.h>



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

void Connect(int socket, const struct sockaddr *address, socklen_t addres_len){
    int res = connect(socket, address, addres_len);
    if (res == -1){
        perror("connect failed ");
        exit(EXIT_FAILURE);
    }
}

void Inet_pton(int af, const char *restrict src, void* restrict dst){
    int res = inet_pton(af, src, dst);  
    if (res == 0){
        printf("inet_pton failed: src does not contain a character "
            "string representing a valid network address in the specified"
            "address famile\n");
        exit(EXIT_FAILURE);
    }
    if (res == -1){
        perror("inet_pton failed");
        exit(EXIT_FAILURE);
    }
}

int main (int argc, char* argv[]) {
    int client_socketfd = Socket(AF_INET, SOCK_STREAM ,0);
    struct sockaddr_in adr = {0};
    adr.sin_family = AF_INET;
    adr.sin_port = htons(34543);
    Inet_pton(AF_INET, "127.0.0.1", &adr.sin_addr); // 127.0.0.1 - address of local computer
    Connect(client_socketfd,(struct sockaddr *) &adr, sizeof(adr));

    int end_of_work = 0;
    do{
        char* command_buffer = NULL;
        int size_buffer = 0;
        int index_in_buffer = 0; 

        char c;
        

        c = getchar();
        while (c != '\0' && c != '\n'){
            command_buffer = realloc(command_buffer,size_buffer+=sizeof(char));
            command_buffer[index_in_buffer++] = c;
            c = getchar();
        }
        command_buffer[index_in_buffer++] = c;
        //printf("sizeof command buffer = %lu\n",sizeof(command_buffer));
        //printf("command buffer = %s",command_buffer);
        send(client_socketfd,command_buffer,sizeof(command_buffer),0);
      
        // /* ............................ */
        if (command_buffer[1] == '?'){
            ssize_t return_status;
            int received_int = 0;
            return_status = read(client_socketfd, &received_int, sizeof(received_int));
            if (return_status > 0) {
                printf("Number_increase_parameter = %d\n", ntohl(received_int));
            }
            else {
                // Handling erros here
                perror("error received number form server");
                return 1;
            }
        }
        else if (command_buffer[1] == '+'){
            char buf[256];
            int number_of_received_bytes;
            number_of_received_bytes = recv(client_socketfd, buf, sizeof(buf),0);
            // //write(STDOUT_FILENO, buf,number_of_received_bytes);
            printf("Answer from server = %s\n",buf);
        }
        else if (command_buffer[1] == '-'){
            end_of_work = 1;
            break;
        }
        else{
            ssize_t return_status;
            int received_int = 0;
            return_status = read(client_socketfd, &received_int, sizeof(received_int));
            if (return_status > 0) {
                printf("Number + Number_increase_parameter = %d\n", ntohl(received_int));
            }
            else {
                // Handling erros here
                perror("error received number form server");
                return 1;
            }
        }
    }while (end_of_work != 1);
    close(client_socketfd);
    return 0;
}