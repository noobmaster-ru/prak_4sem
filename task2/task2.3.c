#include <stdio.h>

void fib1(long int a) 
{
    long int fi,fi_1,fi_2,i;

    if ( a == 0) 
    {
        printf("%ld's number of Fibonacci = %d\n",a,0);
    }
    else if ( a == 1)
    {
        printf("%ld's number of Fibonacci = %d\n",a,1); 
    }
    else 
    {
        i = 1;
        fi_2 = 0; 
        fi_1 = 1;
        fi = fi_2 + fi_1;
        i += 1;
        while (i != a)
        {
            fi_2 = fi_1;
            fi_1 = fi;
            fi = fi_2 + fi_1;
            i += 1;
        }
        printf(" %ld's number of Fibonacci = %ld\n",a,fi);
    }
}

int fib2(long int a)
{
    if ( a == 0) 
    {
       return 0;
    }
    else if ( a == 1)
    {
       return 1; 
    }
    else    
    {
         
        return fib2(a-2) + fib2(a-1);
    }  
}
int main()
{
    long int a;
    printf("Enter numbers: ");
    while (scanf("%ld",&a) != EOF) 
    {
        printf(" iterative: ");
        fib1(a);
        printf(" recursion: ");
        printf(" %ld's number of Fibonacci = %d\n\n",a,fib2(a));
        // fib1 faster than fib2
    }
    return 0;
}