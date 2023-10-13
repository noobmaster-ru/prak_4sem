#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct node *link; // pointer to list node

typedef char* elemtype;    /*  list element type */

typedef struct node
{                  /* list node type */
    elemtype elem; /* element type */
    link next;     /* pointer to the next node */
} node;

typedef link list; /* list type (pointer to the first node) */

list lst, lst1, p, p1;


int main() {
    char str[256];
    char* s;
    int ret, counter, k;
    elemtype last_elem;


    // create list
    printf("Enter strings: ");
    k = 0;
    while (scanf("%s", str) != EOF){
        if (lst == NULL) {
            lst = (link) malloc(sizeof(node));
            s = (char *)malloc(strlen(str) * sizeof(char));
            strcpy(s, str);

            lst ->elem = s;
            lst1 = lst;
            k++;
        }
        else {
            s = (char *)malloc(strlen(str) * sizeof(char));
            strcpy(s, str);
            lst1->next = (link)malloc(sizeof(node));

            lst1 = lst1->next;
            lst1->elem = s;
            lst1->next = NULL;
            k++;
        }
    }
    if (k == 0){
        printf("\n");
    }
    else{
        // find last_element
        p = lst;
        while (p != NULL) {
            last_elem = p->elem;    // last_elem - char*[]
            p = p->next;
        }


        // list before deletes
        printf("\n List before deletes: ");
        p = lst;
        while (p != NULL){
            printf("%s ",p->elem);
            p = p->next;
        }
    
    
        // delete first(s) element(s), which equal last_elem in list
        p1 = lst;
        p = p1->next;
        counter = 0;
        while (p != NULL && counter == 0) {
            ret = strcmp(p1->elem,last_elem);
            if (ret == 0){ // last_elem == first elem
                lst = p;
                free(p1);
                p1 = p;
                p = p->next;
            }
            else{
                counter = 1; // exit the loop
            }
        }



        //delete next elements in list 
        while (p != NULL){
            ret = strcmp(p->elem,last_elem);
            if (ret == 0){      // str1 == str2
                if (p->next != NULL){
                    p1->next = p->next;
                    free(p);
                    p = p1->next;
                }
                else{
                    p = p->next;
                }
            }
            else{
                p1 = p;
                p = p->next;
            }
        }


        // list after deletes
        printf("\n List after deletes: ");
        p = lst;
        while (p != NULL){
            printf("%s ",p->elem);
            p = p->next;
        }
        printf("\n");
    }
    return 0;
}