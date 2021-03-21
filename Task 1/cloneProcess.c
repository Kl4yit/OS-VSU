/*Создаёт копии самой себя и выводит идентификатор текущего и родительского процесса*/
#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>

int main(){
	fork();
	printf("Current PID: %d \n", getpid());
        printf("Parent PID: %d \n", getppid());
        return 0;
}
