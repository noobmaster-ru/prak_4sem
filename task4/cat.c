#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// counter of the strings
int counter = 0;


// copy data from "origin" to "destination"
void print_file(FILE *origin, FILE *destination, int flag_n){
    int c,i = 0;
    if ((flag_n == 1) && (counter == 0)){
        counter++;
        fprintf(destination,"     %d  ",counter);
    }

    while ((c = getc(origin)) != EOF){
        putc(c,destination);
        if (c == '\n'){
            if (flag_n == 1){
                counter++;
                fprintf(destination,"     %d  ",counter);  
            }
        }
    }
}

// copy data from stdin to "destination"
void print_file_stdin(FILE *origin, FILE *destination, int flag_n){
    int c, i = 0;
    char *buf;
    buf  = (char*)malloc(sizeof(char));
    while ((c = getc(origin)) != EOF){
        *(buf+i) = c;
        i++;
        buf = (char*)realloc(buf,i+1);
        if (c == '\n'){
            *(buf+i) = '\0';
            if (flag_n == 1){
                counter++;
                fprintf(destination,"     %d  ",counter);       
            }
            fprintf(destination,buf);
            free(buf);
            i = 0;
            buf = (char*)malloc(sizeof(char));
        }
    }
}

int main(int argc,char* argv[]){
    FILE *fp;
    int pointer = 1, 
        i = 1,
        flag_n = 0;

    if (argc < 2){
       print_file_stdin(stdin,stdout,flag_n);
    }
    else{
        if ((*(argv[1]) == '-') && (*(argv[1]+1) == 'n') && (strlen(argv[1]) >1)){
            flag_n = 1;
            pointer++;
        }
        if (pointer < argc){
            while (pointer < argc){
                if ((fp = fopen(argv[pointer],"r")) == NULL){
                    // if no exist file
                    if (strcmp(argv[pointer],"-") == 0){
                        print_file_stdin(stdin,stdout,flag_n);
                        pointer++;
                    }
                    else{
                        fprintf(stderr,"%s: %s: No such file or directory\n","cat",argv[pointer]);
                        pointer++;
                    }
                }
                else{
                    // if file exist 
                    print_file(fp,stdout,flag_n);
                    fclose(fp);
                    pointer++;
                }
            }
        }
        else{
            print_file_stdin(stdin,stdout,flag_n);
        }
    }
    return 0;
}