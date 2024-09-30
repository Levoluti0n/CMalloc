#include<stdio.h>
#include"includes/free.h"
#include"includes/malloc.h"


int main () {
    int *a = (int*)myMalloc(sizeof(int));
    if(a == NULL) return 0;
    *a = 5;
    printf("%p -> %d \n\n",a,*a);
    myFree(a);

    return 0;
}