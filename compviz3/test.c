#include<stdlib.h>
#include<stdio.h>
int main(){
  int i;
  for(i = 0; i < 100; i++)
    printf("%.2f\n", random()/(1.0*RAND_MAX));
  return 0;
}
