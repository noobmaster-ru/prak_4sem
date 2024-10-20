#include <stdio.h>
#include <stdlib.h>
#include <string.h>



typedef struct tNode *tree;
typedef int elemtype;  

typedef struct tNode{
     elemtype elem;
     elemtype kol;
     tree left;
     tree right;
} tnode;


// // // add element in tree
tree append(tree t, elemtype n) /* root - left - right (KLP Koren'-Levoe-Pravoe) */{
    if (t == NULL){
        t = malloc(sizeof(tnode));
        t->elem = n;
        t->kol = 1;
        t->left = NULL;
        t->right = NULL;
    }
    else if (n == t->elem){
        t->kol += 1;
    }
    else if (n < t->elem ){
        t->left = append(t->left,n);
    }
    else if (n > t->elem){
        t->right = append(t->right,n);
    }
    return t;
}

// // // print a tree in order 
void in_order(tree t) /* left - root - right(LKP) */{
    if (t == NULL){
        return;
    }
    else{
        in_order(t->left);
        for (elemtype i = 1; i <= (t->kol); i++){
            printf("%d ",t->elem);
        }
        in_order(t->right);
    }
}

// delete tree
void delete_tree(tree t){
    if (t == NULL) return;

    delete_tree(t->left);
    delete_tree(t->right);
    free(t);
}
int main(int argc, char *argv[]){
    if (argc < 2 ){
        return 0;
    }
    else{
        int i;
        tree t;
        t  = NULL;
        for (i = 1; i < argc; i++){
            FILE *fp = fopen(argv[i],"r");
            elemtype num;
            while (fscanf(fp, "%d",&num) != EOF ){   //!feof(fp)
                t = append(t,num);
            }
            fclose(fp);
        }
        in_order(t);
        delete_tree(t);
        printf("\n");
    }
    return 0;
}
