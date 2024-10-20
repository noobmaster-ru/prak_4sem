#include <stdio.h>


int main(){
    int a,b,n,i,j;
    scanf("%d%d%d",&a,&b,&n);

    for (i=0; i<n; i++)
         printf(" ");


    for (i = a; i < b-1; i++){
        printf(" %*d",n,i);
    }
    printf(" %*d\n",n,i);

    for (i = a ; i < b ; i++){
        printf("%*d ",n,i);
        for (j = a; j < b-1; j++){
            printf("%*lld ",n,(long long )i*j);
        }
        printf("%*lld\n",n,(long long)i*j);
    }
    return 0;
}