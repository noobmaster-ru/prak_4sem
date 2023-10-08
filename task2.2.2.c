#include <stdio.h>

int main() {
    double x,sum,a,b,pr,delta;
    printf("task2.2.2\n");
    printf("Enter x and odds: ");
    scanf("%lf",&x);
    sum = 0;
    pr = 0;
    scanf("%lf",&a);
    sum *= x;
    sum += a;
    delta = 0;
    while (scanf("%lf",&b) != EOF) {
        pr += delta;
        delta = sum;
        pr *= x;
        pr += a; 
        a = b;
        
        sum *= x;
        sum += b;
    }
    printf("Value of f(x) in x = %lf\n",sum);
    printf("Derevative of f(x) in x = %lf\n",pr);
    return 0;
} 
