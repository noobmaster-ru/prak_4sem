#include <stdio.h>

int main(void) {
    printf("task2.1\n");
    double e,x,x0 = 1.0,x_i,x_i1;
    printf("Enter E = ");
    scanf("%la",&e);

    printf("Enter x = ");
    scanf("%la",&x);
    x_i = x0;
    x_i1 = 0.5*(x_i + (x/x_i));

    while (((x_i - x_i1) >= e) || ((x_i - x_i1) <= -e)) {
        x_i = x_i1;
        x_i1 = 0.5*(x_i + (x/x_i));
    }
    printf("Sqrt(x) = %.10g\n",x_i1);

    return 0;
}
