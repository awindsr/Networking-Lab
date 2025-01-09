#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>


void main(){
    char *args[]= {"./EXEC", NULL};
    execv(args[0], args);
}
