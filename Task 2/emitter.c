/*
 * Программа отправляет другому процессу сигнал SIGUSR1 или SIGUSR2
 * (в зависимости от параметра переданного в командной строке).
 * Процесс, которому нужно отправить сигнал выбирается по его идентификатору PID.
 */
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <string.h>

int main(int argc, char *argv[]){


    if (argc == 3){

        if ((strcmp(argv[2], "SIGUSR1") == 0) || (strcmp(argv[2], "SIGUSR2") == 0))
        {

            int pid = atoi(argv[1]);

            if (strcmp(argv[2], "SIGUSR1") == 0)
            {
                kill(pid, SIGUSR1);
                printf("Signal sent \n");
            } else if (strcmp(argv[2], "SIGUSR2") == 0)
            {
                kill(pid, SIGUSR2);
                printf("Signal sent \n");
            }
        }
        else{
            printf("Argument error \n");
        }
    }
    //Аргументов больше или меньше необходимого
    else{
        printf("Argument error \n");
    }
}