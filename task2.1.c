#include <stdio.h>

int main() {
    printf("task2.1\n");
    double e,x,x0 = 1.0,x_i,x_i1;

    printf("Enter e = ");
    scanf("%la",&e);
    printf("Enter X's:\n");
    while (scanf("%la",&x) != EOF) {
        x0 = 1;
        x_i = x0;
        x_i1 = 0.5*(x_i + (x/x_i));


        while (((x_i - x_i1) >= e) || ((x_i - x_i1) <= -e)) {
            x_i = x_i1;
            x_i1 = 0.5*(x_i + (x/x_i));
        }
        printf("Sqrt(x) = %.10g\n",x_i1);
    }
    printf("\n");
    return 0;
}