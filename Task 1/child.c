/*Код, вызванный exec*/
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
int main(){
    printf("Code replaced with exec\n");
	printf("-Child code- \n");
	printf("Current PID: %d \n", (int)getpid());
	printf("Parent PID: %d \n", (int)getppid());
	return 0;	
}

