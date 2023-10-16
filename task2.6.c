#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct tNode *tree;
typedef int elemtype;  

typedef struct tNode{
     elemtype elem;
     tree left;
     tree right;
} tnode;

tree t;


// // // add element in tree
tree append(tree t, elemtype n) /* root - left - right (KLP Koren'-Levoe-Pravoe) */{
    if (t == NULL){
        t = (tree)malloc(sizeof(tnode));
        t->elem = n;
        t->left = NULL;
        t->right = NULL;
    }
    else{
        if (n < t->elem ){
            t->left = append(t->left,n);
        }
        else if (n > t->elem){
            t->right = append(t->right,n);
        }
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
        printf("%d ",t->elem);
        in_order(t->right);
    }
}



// // // // delete element in tree  // // // 

// find minimum element in right leaf and return the node
tree minValueNode(tree t){
    if (t->left != NULL)
        return minValueNode(t->left);
    return t;
}

tree delete_elem(tree t, elemtype n){
    
    if (t == NULL) return t;

    if (n < t->elem) 
        t->left = delete_elem(t->left,n);
    else if (n > t->elem) 
        t->right = delete_elem(t->right,n);
    else{ 

        // node with only one child or no child
        if (t->left == NULL){
            tree t1 = t->right;
            free(t);
            return t1;
        }
        else if (t->right == NULL){
            tree t1 = t->left;
            free(t);
            return t1;
        }
        // node with two childs
        tree t1 = minValueNode(t->right);
        t->elem = t1->elem;
        t->right = delete_elem(t->right,t1->elem);
    }
    return t;
}
// // // // // // // //


// is there element in tree?
// 0 - no elem in tree , 1 - elem in tree
int find(tree t, elemtype n){
    if (t == NULL)
        return 0; 
    if (t->elem == n)
        return 1;
    if  (t->elem < n)
        return find(t->right,n);
    return find(t->left,n);
}




int main() {
    char s;
    elemtype flag , num;

    printf("Enter numbers:\n");
    tree t;
    t = (tree)malloc(sizeof(tnode));
    t = NULL;
    while (scanf(" %c%d", &s, &num) != EOF){
        if (s == '+') {
            t = append(t,num);
            printf("Tree elements in order: ");
            in_order(t);
            printf("\n");
        }
        if (s == '?'){
            // printf("%c\n",s);
            // printf("%d\n",num);
            if (find(t,num) == 0){
                printf("%d no\n",num);   // elem no in tree 
            }
            else{ 
                printf("%d yes\n",num);   // elem in tree
            }
            printf("Tree elements in order: ");
            in_order(t);
            printf("\n");
        } 
        if (s == '-'){
            if (find(t,num) == 1) // elem  in tree 
                t = delete_elem(t,num);
            printf("Tree elements in order: ");
            in_order(t);
            printf("\n");
        }
    }
    return 0;
}