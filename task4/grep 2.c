#include <errno.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h> 

int main(int argc, char* argv[]){
    int i = 1,
        len_of_descriptors = 0,
        flag = 0,
        flag_v = 0;

    // считываем флаги 
    while ((i < argc) && (*(argv[i]) == '-') && (flag == 0)){
        switch (*(argv[i])){
            case '-':
                for (int pointer = 1; pointer < strlen(argv[i]); pointer++){
                    if (*(argv[i]+pointer) == 'v')
                        flag_v = 1;
                    else{
                        if (strlen(argv[i]) > 2){
                            pointer++;
                            printf("grep: invalid line width: '");
                            while (*(argv[i]+pointer) != '\0'){
                                printf("%c",*(argv[i]+pointer));
                                pointer++;
                            }
                            printf("'\n");
                        }
                        else{
                            printf("grep: invalid option -- '%c'\n",*argv[i]);
                            printf("Try 'grep --help' for more information.\n");
                        }
                        exit(EXIT_FAILURE);
                    }
                } 
                len_of_descriptors++;
                i++;
                break;
            default:
                flag = 1;
                break;
        }
    }


    // create a substring
    i = len_of_descriptors + 1;
    char *substring;
    substring = (char*)malloc(sizeof(argv[i]));
    for (int j = 0; j < strlen(argv[i]); j++){
        *(substring+j) = *(argv[i] + j);
    }

    // open file
    if (i+1 <= argc){
        FILE *fp;
        fp = fopen(argv[i+1],"r");

        if (fp != NULL){
            //find same strings
            int c;
            int flag_end_of_file = 0;
            while (flag_end_of_file == 0){
                char *string = malloc(sizeof(char));
                int pointer = 0,
                    pointer_in_substring = 0,
                    flag_for_print_string = 1,
                    flag_for_comparing_strings = 0;

                while (( c = getc(fp) ) != '\n' && (c != EOF)){
                    *(string+pointer) = (char)c;
                    string = realloc(string,sizeof(char)*strlen(string)+1);
                    pointer++;

                    if (flag_for_comparing_strings == 0){
                        if ((char)c == *(substring+pointer_in_substring)){
                            pointer_in_substring++;
                        }
                        else if (pointer_in_substring == strlen(substring)){
                            flag_for_print_string = 0;
                            flag_for_comparing_strings  = 1;
                        }
                        else{
                            flag_for_print_string = 1;
                            pointer_in_substring = 0;
                        }
                    }
                }
                if (c == EOF){
                    if (flag_for_print_string == 0 && flag_v == 0){
                        printf("%s",string);
                    }
                    else if (flag_v == 1 && flag_for_print_string == 1){
                        printf("%s",string);
                    }
                    flag_end_of_file = 1;
                }
                else{
                    *(string+pointer) = (char)c;
                    string = realloc(string,sizeof(char)*strlen(string)+1);
                    pointer++;
                    *(string+pointer) = '\0';
                    if (flag_for_print_string == 0 && flag_v == 0){
                        printf("%s",string);
                    }
                    else if (flag_v == 1 && flag_for_print_string == 1){
                        printf("%s",string);
                    }
                }
                free(string);
            }
            fclose(fp);
        }
        else{
            printf("error");
        }
    }
    else{
        printf("error");
    }
    free(substring);
    return 0;
}