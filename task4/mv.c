#include <stdio.h>
#include <dirent.h>
#include <string.h>
#include <sys/stat.h>
#include <stdlib.h>



#define S_IFMTmy    0170000 // позволяет “вырезать” тип файла
#define S_IFDIRmy   0040000 // каталог
#define S_IFCHRmy   0020000 // байт-ориентированный
#define S_IFBLKmy   0060000 // блок-ориентированный
#define S_IFREGmy   0100000 // обычный
#define S_IFLNKmy   0120000 // символическая ссылка
#define S_IFSOCKmy  0140000 // сокет
#define S_ISUIDmy   0004000 // установка идентификатора пользователя при выполнении (изменяется eUID процесса)
#define S_ISGIDmy   0002000 // установка идентификатора группы при выполнении (изменяется eGID процесса)
#define S_ISVTXmy   0001000 // для обычного файла - сохранить текст программы (машинный код) в ОП после завершения процесса; 

// показать тип файла в первой позиции выходной строки 
char determinate_file_type ( int st_mode ) {                                   
    switch ( st_mode & S_IFMTmy ){
        case S_IFDIRmy:   return 'd';
        case S_IFCHRmy:   return 'c';
        case S_IFBLKmy:   return 'b';
        case S_IFREGmy:   return '-';
        case S_IFLNKmy:   return 'l';
        case S_IFSOCKmy:  return 's';
    }
}


// is directory?
int is_directory(char *path_name){
    struct stat     statv;
    if ( lstat ( path_name, &statv ) ){ 
        perror ( path_name ); 
        return 1;
    }
    
    //  показать имя файла
    char  file_type = determinate_file_type ( statv.st_mode );
    if (file_type == 'd')
        return 0;
    else 
        return 1;
}

int main(int argc, char* argv[]){
    struct dirent *d;
    DIR *dh = opendir(".");



    char *directory = ".";
    while ((d = readdir(dh)) != NULL){

        if (strcmp(d->d_name,argv[2]) == 0 ){
            printf("%s\n",d->d_name);
            // buffer1 == ./argv[1]
            char *buffer1 = malloc(sizeof(directory)+ 1 + strlen(argv[1]));
            strcpy(buffer1,directory);
            strcpy(buffer1+strlen(directory),"/");
            strcpy(buffer1+strlen(directory) + 1 ,argv[1]);

            // buffer2 = ./argv[2]
            char *buffer2 = malloc(sizeof(directory)+ 1 + strlen(d->d_name));
            strcpy(buffer2,directory);
            strcpy(buffer2+strlen(directory),"/");
            strcpy(buffer2+strlen(directory) + 1 ,d->d_name);

            if ((is_directory(buffer2) == 0) && (is_directory(buffer1) != 0 )){ 

                // argv[1] - file , argv[2] - dir  =>  put file to dir

                printf("directory_name = %s\n",buffer2);
                FILE *file_read = fopen(argv[1],"r");
                if (file_read != NULL){
                        
                    struct dirent *d;
                    printf("\n");
                    FILE *file_create;
                    if (file_create != NULL){
                        char *filename = malloc(strlen(buffer2)*sizeof(char)+ 1 + strlen(argv[1]));
                        strcpy(filename,buffer2);
                        strcpy(filename + strlen(buffer2) ,"/");
                        strcpy(filename + strlen(buffer2) + 1 ,argv[1]);

                        printf("way to filename = %s",filename);
                        file_create = fopen(filename,"a+");
                        int c;
                        while ((c = getc(file_read)) != EOF ){
                            putc(c,file_create);
                        }
                        remove(argv[1]);
                        fclose(file_create);
                        fclose(file_read);
                        free(filename);
                    }
                }
            }
            else if ((is_directory(buffer1) == 0) && (is_directory(buffer2) == 0 )) {

                // argv[1] - dir1 , argv[2] - dir2 => move dir1 to dir2

                // dirname - ./tmp
                char *dirname2 = malloc(strlen(buffer2)*sizeof(char)+ 1 + strlen(argv[1]));
                strcpy(dirname2,buffer2);
                strcpy(dirname2 + strlen(buffer2) ,"/");
                strcpy(dirname2 + strlen(buffer2) + 1 ,argv[1]);

                // https://techoverflow.net/2013/04/05/how-to-use-mkdir-from-sysstat-h/ - to create directories
                mkdir(dirname2,S_IRUSR | S_IWUSR | S_IXUSR); // all rights only to user
                printf("dirname2  = %s\n",dirname2);

                char *dirname1 = malloc(strlen(buffer1)*sizeof(char)+ 1 + strlen(argv[1]));
                strcpy(dirname1,buffer1);
                printf("dirname1 = %s\n",dirname1);
                struct dirent *d_aa;
                DIR *dh_aa = opendir(dirname1);
                if (dh_aa != NULL){
                    while ((d_aa = readdir(dh_aa)) != NULL){
                        if (d_aa->d_name[0] != '.'){
                            char *open_file_in_dir1 = malloc(strlen(dirname1)*sizeof(char) + strlen(d_aa->d_name));
                            strcpy(open_file_in_dir1, dirname1);
                            strcpy(open_file_in_dir1 + strlen(dirname1) ,"/");
                            strcpy(open_file_in_dir1+strlen(dirname1)+1,d_aa->d_name);

                            //printf("open file in dir1 = %s\n\n",open_file_in_dir1);
                            FILE *file_read = fopen(open_file_in_dir1,"r");
                            if (file_read != NULL){
                                //printf("dirname2 = %s\n\n",dirname2);
                                char *dirname2_new = (char*)malloc(strlen(dirname2)*sizeof(char) + 1 + strlen(d_aa->d_name));
                                strcpy(dirname2_new,dirname2);
                                strcpy(dirname2_new + strlen(dirname2_new) ,"/");
                                strcpy(dirname2_new + strlen(dirname2_new),d_aa->d_name);
                                printf("dirname2_new = %s\n\n",dirname2_new);
                                FILE *file_create;
                                if (file_create != NULL){
                                    file_create = fopen(dirname2_new,"a+");
                                    int c;
                                    while ((c = getc(file_read)) != EOF ){
                                        putc(c,file_create);
                                    }
                                    fclose(file_read);
                                    fclose(file_create);
                                    free(open_file_in_dir1);
                                    free(dirname2_new);
                                }
                            }
                        }
                    }
                    closedir(dh_aa);
                }

                dh_aa = opendir(dirname1);
                if (dh_aa != NULL){
                    while ((d_aa = readdir(dh_aa)) != NULL){
                        char *open_file_in_dir1 = malloc(strlen(dirname1)*sizeof(char) + strlen(d_aa->d_name));
                        strcpy(open_file_in_dir1, dirname1);
                        strcpy(open_file_in_dir1 + strlen(dirname1) ,"/");
                        strcpy(open_file_in_dir1+strlen(dirname1)+1,d_aa->d_name);
                        remove(open_file_in_dir1);
                        free(open_file_in_dir1);
                    }
                    printf("buffer1 = %s\n",buffer1);
                    remove(buffer1);
                    closedir(dh_aa);
                }
                free(dirname1);
                free(dirname2);
            }
            else if ((is_directory(buffer2) != 0) && (is_directory(buffer1) != 0 )){

                // argv[1] - file1 , argv[2] - file2 => rename file1 to file2 
                rename(argv[1],argv[2]);
            }
            free(buffer1);
            free(buffer2);
            break;
        }
    }
    
    closedir(dh);
    return 0;
}