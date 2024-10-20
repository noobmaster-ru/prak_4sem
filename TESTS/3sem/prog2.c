#include <stdio.h>

int main(){
    int c;
    long long sum=0;
    while ((c = getchar()) != EOF){
        if ((c >= '0') && (c <= '9')){
            sum +=  (c - '0');
        }
        if ((c >= 'a') && (c <= 'f')){
            sum += 10 + (c - 'a');
        }
        if ((c >= 'A') && (c <= 'F')){
            sum += 10 + (c - 'A');
        }
    }
    printf("%lld\n",sum);
}