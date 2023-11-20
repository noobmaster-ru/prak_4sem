#include <stdio.h>

int main() {
    double x,sum,a;
    printf("task2.2.1\n");
    printf("Enter x and odds: ");
    scanf("%lf",&x);
    sum = 0;
    while (scanf("%lf",&a) != EOF) {
        sum *= x;
        sum += a;
    }
    printf("Value of f(x) in x = %lf\n",sum);
    return 0;
}