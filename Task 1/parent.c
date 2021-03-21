/*Выводит идентификаторы текущего и родительского процесса, затем заменяет процесс и код программы вызовом exec*/
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

int main(){
	printf("-Parent code-\n");
	char *args[]={"./child", NULL};
	printf("Current PID: %d \n", getpid());
	printf("Parent PID: %d \n", getppid());
	execvp(args[0],args);
	return 0;	
}
