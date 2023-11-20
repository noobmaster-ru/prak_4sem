#include <stdio.h>

int main() {
    double x,sum,a,b,pr,delta,integral;
    int n;
    printf("task2.2.3\n");

    printf("Enter n , x and odds: ");
    scanf("%d",&n);
    scanf("%lf",&x);
    sum = 0;
    pr = 0;
    integral = 0;
    scanf("%lf",&a);
    sum *= x;
    sum += a;
    integral = a*x/(n+1);
    n -= 1;
    delta = 0;
    while (scanf("%lf",&b) != EOF) {
        pr += delta;
        delta = sum;
        pr *= x;
        pr += a; 
        a = b;
        
        sum *= x;
        sum += b;

        integral *= x;
        integral += b*x/(n+1);
        n -= 1;
    }
    printf("Value of f(x) in x = %lf\n",sum);
    printf("Derevative of f(x) in x = %lf\n",pr);
    printf("Integral of f(x) from 0 to x = %lf\n",integral);
    return 0;
} 
