#include <stdio.h>

int main() {
    double x,sum,a,pr;
    scanf("%lf",&x);
    sum = 0;
    pr = 0;
    while (scanf("%lf",&a) != EOF) {
        sum *= x;
        sum += a;
        pr += pr;
        pr *= x;

    }
    printf("%lf\n",sum);
    return 0;
} 
