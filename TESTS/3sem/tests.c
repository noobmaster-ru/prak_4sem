#include <stdio.h>

#define N 5
int main(){
   char str[N];
   while (fscanf(stdin,"%5s",str) != EOF){
      printf("%s\n",str);
   }
}