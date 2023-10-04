#include <stdio.h>

int main() {
    double x,sum,a;
    scanf("%lf",&x);
    sum = 0;
    while (scanf("%lf",&a) != EOF) {
        sum *= x;
        sum += a;
    }
    printf("%lf\n",sum);
    return 0;
} 
