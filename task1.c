#include <stdio.h>

int main() {
    printf("task 1.1\n");
    printf("%lu %s \n",sizeof(short)," - short");
    printf("%lu %s \n",sizeof(int)," - int");
    printf("%lu %s \n",sizeof(long)," - long");
    printf("%lu %s \n",sizeof(float)," - float");
    printf("%lu %s \n",sizeof(double)," - double");
    printf("%lu %s \n\n",sizeof(long double)," - long double");

    printf("task 1.2\n");
    char c = -1;
    if (c < 0) {
        printf("%s","signed\n\n");
    }
    else {
        printf("%s","unsigned\n\n");
    }

    printf("task1.6\n");
    int x;
    int y = 3;
    int z = 1;
    printf("x = %d \n", x);
    printf("y = %d \n", y);
    printf("z = %d \n\n", z);

    printf("task1.8\n");
    int x1 = 12;
    int x2 = 11;
    int x3 = -4;
    int x4 = -3;

    printf(" 12 mod 11 = %d\n",(x1 % x2 ));
    printf(" 11 mod 12 = %d\n\n",(x2 % x1 ));

    printf(" 12 mod -4 = %d\n", (x1 % x3));
    printf(" 12 mod 11 = %d\n\n", (x1 % x2));




    printf(" -4 mod 12 = %d\n", (x3 % x1));
    printf(" -4 mod 11 = %d\n\n", (x3 % x2));

    printf(" -3 mod -4 = %d\n",(x4 % x3));
    printf(" -4 mod -3 = %d\n\n",(x3 % x4));

    printf("end of the world");
    return 0;

}

