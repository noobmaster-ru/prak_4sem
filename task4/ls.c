#include <sys/types.h>
#include <sys/stat.h>
#include <pwd.h>
#include <stdio.h>
#include <time.h>
#include <grp.h>
#include <errno.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>

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

#ifndef  MAJOR
  #define MINOR_BITS 8 // !
  #define MAJOR(dev) ((unsigned) dev >> MINOR_BITS)
  #define MINOR(dev) (dev & MINOR_BITS)
#endif

// defined  the size of file int 512-byte blocks for total
long int defined_sizeblocks_of_file( char * path_name , int op_r, int op_l, int op_g){
    struct stat     statv;
    struct passwd  *pw_d;
    if (op_l == 1 || op_g == 1){
        lstat ( path_name, &statv );
        return statv.st_blocks;
    }
}

// define the total
void defined_total(char *dir,int op_r, int op_l, int op_g){
    struct dirent *d;
    DIR *dh = opendir(dir);
    long int total = 0;
    // create a list of filenames
    while ((d = readdir(dh)) != NULL){
        if (d->d_name[0] != '.'){
            if (op_r == 1){
                char *buffer = malloc(sizeof(dir)+ 1 + strlen(d->d_name));
                strcpy(buffer,dir);
                strcpy(buffer+strlen(dir),"/");
                strcpy(buffer+strlen(dir) + 1 ,d->d_name);
                total += defined_sizeblocks_of_file(buffer, op_r, op_l, op_g);
                free(buffer);
            }
            else{
                total += defined_sizeblocks_of_file(d->d_name, op_r, op_l, op_g);
            }
        }

    }
    closedir(dh);
    printf("total %ld\n",total/2); // 512-byte not 1024-byte
} 

void blue () {
  printf("\033[1;34m");
}

void green() {
  printf("\033[1;32m");
}

void reset () {
  printf("\033[0m");
}

// determinate object file
int determinate_object_file( int st_mode ){
    static const char xtbl[10] = "rwxrwxrwx";
    char     amode[10], ideal[10] = "rwxr-xr-x";

    int      i, j;

    for ( i = 0, j = ( 1 << 8 ); i < 9; i++, j >>= 1 )
        amode[i] = ( st_mode&j ) ? xtbl[i]: '-';
    if ( st_mode & S_ISUIDmy )   amode[2]= 's';
    if ( st_mode & S_ISGIDmy )   amode[5]= 's';
    if ( st_mode & S_ISVTXmy )   amode[8]= 't';
    amode[9]='\0';

    if (strcmp(ideal,amode) == 0)
        return 0;
    else    
        return 1;
}

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

// показать тип файла в первой позиции выходной строки 
void display_file_type ( int st_mode ) {                                   
    switch ( st_mode & S_IFMTmy ){
        case S_IFDIRmy:  putchar ( 'd' ); return;
        case S_IFCHRmy:  putchar ( 'c' ); return;
        case S_IFBLKmy:  putchar ( 'b' ); return;
        case S_IFREGmy:  putchar ( '-' ); return;
        case S_IFLNKmy:  putchar ( 'l' ); return;
        case S_IFSOCKmy: putchar ( 's' ); return;
    }
} 

// показать права доступа для владельца, группы и прочих пользователей, а также все спец.флаги 
void display_permission ( int st_mode ){
    static const char xtbl[10] = "rwxrwxrwx";
    char     amode[10];
    int      i, j;
    for ( i = 0, j = ( 1 << 8 ); i < 9; i++, j >>= 1 )
        amode[i] = ( st_mode&j ) ? xtbl[i]: '-';
    if ( st_mode & S_ISUIDmy )   amode[2]= 's';
    if ( st_mode & S_ISGIDmy )   amode[5]= 's';
    if ( st_mode & S_ISVTXmy )   amode[8]= 't';
    amode[9]='\0';
    printf ( "%s ",amode );
}

// перечислить атрибуты одного файла
void print_flag_l( char * path_name,char* answer){
    struct stat     statv;
    struct passwd  *pw_d;
    struct tm *t;
    struct group *g;
    char time[26];
    if ( lstat ( path_name, &statv ) ){ 
        perror ( path_name ); 
        return;
    }
    display_file_type ( statv.st_mode );
    display_permission ( statv.st_mode );
    printf ( "%d ",statv.st_nlink );  // значение счетчика жестких связей
    pw_d = getpwuid ( statv.st_uid ); // преобразовать UID в имя пользователя
    printf ( "%s ",pw_d->pw_name );   // и напечатать его


    // print group id
    g = getgrgid(statv.st_gid);
    printf("%6s ",g->gr_name);

    if (    ( statv.st_mode & S_IFMTmy) == S_IFCHRmy  || ( statv.st_mode & S_IFMTmy) == S_IFBLKmy )
        // показать старший и младший номера устройства
        printf ( "%6d, %6d",MAJOR(statv.st_rdev), MINOR(statv.st_rdev) );
    else
        // или размер файла
        printf ( "%5d", statv.st_size );
    

    // time of last modification 
    t = localtime(&statv.st_mtime);
    strftime(time,sizeof(time), " %b %d %H:%M ",t);
    printf("%s",time);

    //  показать имя файла
    char  file_type = determinate_file_type ( statv.st_mode );
    if (file_type == 'd'){
        blue();
        printf("%s\n",answer);
        reset();
    }
    else if (determinate_object_file(statv.st_mode ) == 0){
        green();
        printf("%s\n",answer);
        reset();
    }
    else{
        printf ( "%s\n", answer );
    }
}

// print with flag -g
void print_flag_g( char * path_name, char* answer){
    struct stat     statv;
    struct passwd  *pw_d;
    struct tm *t;
    struct group *g;
    char time[26];
    if ( lstat ( path_name, &statv ) ){ 
        perror ( path_name ); 
        return;
    }
    display_file_type ( statv.st_mode );
    display_permission ( statv.st_mode );
    printf ( "%d ",statv.st_nlink );  // значение счетчика жестких связей

    // print group id
    g = getgrgid(statv.st_gid);
    printf("%6s ",g->gr_name);

    if (    ( statv.st_mode & S_IFMTmy) == S_IFCHRmy  || ( statv.st_mode & S_IFMTmy) == S_IFBLKmy )
        // показать старший и младший номера устройства
        printf ( "%6d, %6d",MAJOR(statv.st_rdev), MINOR(statv.st_rdev) );
    else
        // или размер файла
        printf ( "%5d", statv.st_size );
    

    // time of last modification 
    t = localtime(&statv.st_mtime);
    strftime(time,sizeof(time), " %b %d %H:%M ",t);
    printf("%s",time);

    //  показать имя файла
    char  file_type = determinate_file_type ( statv.st_mode );
    if (file_type == 'd'){
        blue();
        printf("%s\n",answer);
        reset();
    }
    else if (determinate_object_file(statv.st_mode ) == 0){
        green();
        printf("%s\n",answer);
        reset();
    }
    else{
        printf ( "%s\n",answer);
    }
}

//print without flags
void print_without_flags( char * path_name, char* answer){
    struct stat     statv;
    if ( lstat ( path_name, &statv ) ){ 
        perror ( path_name ); 
        return;
    }
    char  file_type = determinate_file_type ( statv.st_mode );
    if (file_type == 'd'){
        blue();
        printf("%s  ",answer);
        reset();
    }
    else if (determinate_object_file(statv.st_mode ) == 0){
        green();
        printf("%s  ",answer);
        reset();
    }
    else{
        printf ( "%s  ",answer);
    }
}


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

//print with flag -R
void print_flag_r(char *directory, int flag_a,int flag_l, int flag_g){
    struct dirent *d;
    DIR *dh = opendir(directory);

    if (strcmp(directory,".") == 0){    
        if (flag_l == 1){
            int total = 0;
            defined_total(directory, 0, flag_l, flag_g);
            while ((d = readdir(dh)) != NULL){
                if (flag_a == 1){
                    print_flag_l(d->d_name,d->d_name);
                }
                else{
                    if (d->d_name[0] != '.'){
                        print_flag_l(d->d_name,d->d_name);
                    }
                }
            }
        }
        else if (flag_g == 1){
            int total = 0;
            defined_total(directory, 0, flag_l, flag_g);
            while ((d = readdir(dh)) != NULL){
                if (flag_a == 1){
                    print_flag_g(d->d_name,d->d_name);
                }
                else{
                    if (d->d_name[0] != '.'){
                        print_flag_g(d->d_name,d->d_name);
                    }
                }
            }
        }
        else{
            while ((d = readdir(dh)) != NULL){
                if (flag_a == 1){
                    print_without_flags(d->d_name,d->d_name);
                }
                else{
                    if (d->d_name[0] != '.'){
                        print_without_flags(d->d_name,d->d_name);
                    }
                }
            }
        }
    }
    else {
        if (flag_l == 1){
            int total = 0;
            defined_total(directory, 1, flag_l, flag_g);
            while ((d = readdir(dh)) != NULL){
                if (flag_a == 1){
                    char *buffer = malloc(sizeof(directory)+ 1 + strlen(d->d_name));
                    strcpy(buffer,directory);
                    strcpy(buffer+strlen(directory),"/");
                    strcpy(buffer+strlen(directory) + 1 ,d->d_name);
                    if (d->d_name[0] == '.'){
                        print_flag_l(d->d_name,d->d_name);
                    }
                    else{
                        print_flag_l(buffer,d->d_name);
                    }
                    free(buffer);
                }
                else{
                    if (d->d_name[0] != '.'){
                        char *buffer = malloc(sizeof(directory)+ 1 + strlen(d->d_name));
                        strcpy(buffer,directory);
                        strcpy(buffer+strlen(directory),"/");
                        strcpy(buffer+strlen(directory) + 1 ,d->d_name);
                        print_flag_l(buffer,d->d_name);
                        free(buffer);
                    }
                }
            }
        }
        else if (flag_g == 1){
            int total = 0;
            defined_total(directory, 1, flag_l, flag_g);
            while ((d = readdir(dh)) != NULL){
                if (flag_a == 1){
                    char *buffer = malloc(sizeof(directory)+ 1 + strlen(d->d_name));
                    strcpy(buffer,directory);
                    strcpy(buffer+strlen(directory),"/");
                    strcpy(buffer+strlen(directory) + 1 ,d->d_name);
                    if (d->d_name[0] == '.'){
                        print_flag_g(d->d_name,d->d_name);
                    }
                    else{
                        print_flag_g(buffer,d->d_name);
                    }
                    free(buffer);
                } 
                else{
                    if (d->d_name[0] != '.'){
                        char *buffer = malloc(sizeof(directory)+ 1 + strlen(d->d_name));
                        strcpy(buffer,directory);
                        strcpy(buffer+strlen(directory),"/");
                        strcpy(buffer+strlen(directory) + 1 ,d->d_name);
                        print_flag_g(buffer,d->d_name);
                        free(buffer);
                    }
                }
            }
        }
        else{
            while ((d = readdir(dh)) != NULL){
                if (flag_a == 1){
                    char *buffer = malloc(sizeof(directory)+ 1 + strlen(d->d_name));
                    strcpy(buffer,directory);
                    strcpy(buffer+strlen(directory),"/");
                    strcpy(buffer+strlen(directory) + 1 ,d->d_name);
                    print_without_flags(buffer,d->d_name);
                    free(buffer);
                }
                else{
                    if (d->d_name[0] != '.'){
                        char *buffer = malloc(sizeof(directory)+ 1 + strlen(d->d_name));
                        strcpy(buffer,directory);
                        strcpy(buffer+strlen(directory),"/");
                        strcpy(buffer+strlen(directory) + 1 ,d->d_name);
                        print_without_flags(buffer,d->d_name);
                        free(buffer);
                    }
                }
            }
        }
    }   
    closedir(dh);
    return;
}

void ls(char *directory, int flag_a, int flag_r, int flag_l, int flag_g){
    struct dirent *d;
    DIR *dh = opendir(directory);

    if (flag_a == 1){
        // print with flag -a
        if (flag_r == 1){
            // опишем структуры данных - список слов , в которую поместим имена все папок в директории
            typedef struct node *link; // pointer to list node
            typedef char* elemtype;    /*  list element type */
            typedef struct node
            {                  /* list node type */
                elemtype elem; /* element type */
                link next;     /* pointer to the next node */
            } node;
            typedef link list; /* list type (pointer to the first node) */
            list lst, lst1, p;
            char* s;

            lst = NULL;
            // create a list with name of directories 
            lst = (link)malloc(sizeof(node));
            s = (char *)malloc(1 * sizeof(char) + 1);
            strcpy(s,".");
            lst->elem = s;
            lst1 = lst;
            while ((d = readdir(dh)) != NULL){
                if (d->d_name[0] != '.'){
                    if (is_directory(d->d_name) == 0){
                        if (lst == NULL) {
                            lst = (link) malloc(sizeof(node));
                            s = (char *)malloc(strlen(d->d_name) * sizeof(char) + 1) ;
                            strcpy(s, d->d_name);

                            lst->elem = s;
                            lst1 = lst;
                        }
                        else {
                            s = (char *)malloc(strlen(d->d_name) * sizeof(char) + 1);
                            strcpy(s, d->d_name);
                            lst1->next = (link)malloc(sizeof(node));

                            lst1 = lst1->next;
                            lst1->elem = s;
                            lst1->next = NULL;
                        }
                    }
                }
            }   
            // теперь пробегаемся по списку, в котором лежат имена всех папок в директории и печатаем
            p = lst;
            while (p != NULL){
                if (p->elem[0] == '.'){
                    printf(".:\n");
                    print_flag_r(p->elem,flag_a,flag_l,flag_g);
                    printf("\n");
                }
                else{
                    char *dirname = (char*)malloc(sizeof(char)*2 + strlen(p->elem));
                    dirname[0] = '.';
                    dirname[1] = '/';
                    int i = 2;
                    while ( i-2 < strlen(p->elem)){
                        dirname[i] = p->elem[i-2];
                        i++;
                    }
                    dirname[strlen(p->elem)+2] = '\0';
                    printf("\n");
                    printf("\n%s:\n",dirname);
                    // .   ./txt   ./tmp
                    print_flag_r(dirname,flag_a,flag_l,flag_g);
                    printf("\n");
                    free(dirname);
                }
                p = p->next;
            }

            // delete list
            while (lst != NULL){
                p = lst;
                lst = lst->next;
                free(p->elem);
                free(p);
            }
        }
        else if (flag_l == 1){
            // flag -l
            int total = 0;
            defined_total(directory, flag_r, flag_l, flag_g);
            while ((d = readdir(dh)) != NULL){
                print_flag_l(d->d_name,d->d_name);
            }
        }
        else if (flag_g == 1){
            //  flag -g 
            int total = 0;
            defined_total(directory, flag_r, flag_l, flag_g);
            while ((d = readdir(dh)) != NULL){
                print_flag_g(d->d_name,d->d_name);
            }        
        }
        else{
            // without flags
            while ((d = readdir(dh)) != NULL){
                print_without_flags(d->d_name,d->d_name);
            }
            printf("\n"); 
        }
    }
    else if (flag_r == 1){
        // опишем структуру данных - список слов , в которую поместим имена все папок в директории
        typedef struct node *link; // pointer to list node
        typedef char* elemtype;    /*  list element type */
        typedef struct node
        {                  /* list node type */
            elemtype elem; /* element type */
            link next;     /* pointer to the next node */
        } node;
        typedef link list; /* list type (pointer to the first node) */
        list lst, lst1, p;
        char* s;

        lst = NULL;
        // create a list with name of directories 
        lst = (link)malloc(sizeof(node));
        s = (char *)malloc(1 * sizeof(char) + 1);
        strcpy(s,".");
        lst->elem = s;
        lst1 = lst;
        while ((d = readdir(dh)) != NULL){
            if (d->d_name[0] != '.'){
                if (is_directory(d->d_name) == 0){
                    if (lst == NULL) {
                        lst = (link) malloc(sizeof(node));
                        s = (char *)malloc(strlen(d->d_name) * sizeof(char) + 1) ;
                        strcpy(s, d->d_name);

                        lst->elem = s;
                        lst1 = lst;
                    }
                    else {
                        s = (char *)malloc(strlen(d->d_name) * sizeof(char) + 1);
                        strcpy(s, d->d_name);
                        lst1->next = (link)malloc(sizeof(node));

                        lst1 = lst1->next;
                        lst1->elem = s;
                        lst1->next = NULL;
                    }
                }
            }
        }   

        // теперь пробегаемся по списку, в котором лежат имена всех папок в директории и печатаем
        p = lst;
        while (p != NULL){
            if (p->elem[0] == '.'){
                printf(".:\n");
                print_flag_r(p->elem,flag_a,flag_l,flag_g);
                printf("\n");
            }
            else{
                char *dirname = (char*)malloc(sizeof(char)*2 + strlen(p->elem));
                dirname[0] = '.';
                dirname[1] = '/';
                int i = 2;
                while ( i-2 < strlen(p->elem)){
                    dirname[i] = p->elem[i-2];
                    i++;
                }
                dirname[strlen(p->elem)+2] = '\0';
                printf("\n");
                printf("\n%s:\n",dirname);

                print_flag_r(dirname,flag_a,flag_l,flag_g);
                printf("\n");
                free(dirname);
            }
            p = p->next;
        }

        // delete list
        while (lst != NULL){
            p = lst;
            lst = lst->next;
            free(p->elem);
            free(p);
        }
    }
    else if (flag_l == 1){
        // only flag -l
        int total = 0;
        defined_total(directory, flag_r, flag_l, flag_g);
        while ((d = readdir(dh)) != NULL){
            if (d->d_name[0] != '.'){
                print_flag_l(d->d_name,d->d_name);
            }
        }
    }
    else if (flag_g == 1){
        // only flag -g 
        int total = 0;
        defined_total(directory, flag_r, flag_l, flag_g);
        while ((d = readdir(dh)) != NULL){
            if (d->d_name[0] != '.'){
                print_flag_g(d->d_name,d->d_name);
            }
        }        
    }
    else{
        // without flags
        while ((d = readdir(dh)) != NULL){
            if (d->d_name[0] != '.'){
                print_without_flags(d->d_name,d->d_name);
            }
        }
        printf("\n"); 
    }
    closedir(dh);
    return;
}

// главный цикл отображения атрибутов для каждого файла
int main( int argc, char * argv[] ){
    int i = 1,
        len_of_descriptors = 0,
        flag = 0,
        flag_r = 0, 
        flag_l = 0, 
        flag_g = 0,
        flag_a = 0;

    // считываем флаги 
    while ((i < argc) && (*(argv[i]) == '-') && (flag == 0)){
        switch (*(argv[i])){
            case '-':
                for (int pointer = 1; pointer < strlen(argv[i]); pointer++){
                    if (*(argv[i]+pointer) == 'R')
                        flag_r = 1;
                    else if (*(argv[i]+pointer) == 'l' && flag_g == 0){
                        flag_l = 1;
                    }
                    else if (*(argv[i]+pointer) == 'g'){
                        flag_l = 0;
                        flag_g = 1;
                    }
                    else if (*(argv[i]+pointer) == 'a'){
                        flag_a = 1;
                    }
                    else{
                        if (flag_g == 1 && flag_l == 0){
                            continue;
                        }
                        else{ 
                            if (strlen(argv[i]) > 2){
                                pointer++;
                                printf("ls: invalid line width: '");
                                while (*(argv[i]+pointer) != '\0'){
                                    printf("%c",*(argv[i]+pointer));
                                    pointer++;
                                }
                                printf("'\n");
                            }
                            else{
                                printf("ls: invalid option -- '%c'\n",*argv[i]);
                                printf("Try 'ls --help' for more information.\n");
                            }
                            exit(EXIT_FAILURE);
                        }
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

    if (argc == 1){
        // если только один ls
        ls(".",flag_a,flag_r, flag_l, flag_g);
    }
    else if (len_of_descriptors + 1  == argc)
        // если ls -флаги -флаги
        ls(".",flag_a,flag_r, flag_l, flag_g);
    else{
        i = len_of_descriptors + 1;
        while (i < argc){
            if (flag_l == 1){
                print_flag_l(argv[i],argv[i]);
            }
            else if (flag_g == 1){
                print_flag_g(argv[i],argv[i]);
            }
            else if (flag_r == 1 ){
                print_flag_r(argv[i],flag_a,flag_l,flag_g);
            }
            else{
                print_without_flags(argv[i],argv[i]);
            }
            i++;
        }
    }
    
    return 0;
}